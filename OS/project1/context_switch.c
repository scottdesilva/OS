/**********************************************************

 context_switch.c : measures the time between a context switch
 Scott De Silva & Shaughn Seepaul

**********************************************************/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <sched.h>
#include <math.h>
#define SAMPLE_SIZE 100

int main()
{
  pid_t pid;
  int pp[2], cp[2], i;
  double time_stmp;
  struct timespec start, end;


  cpu_set_t mask;       //define bit mask
  CPU_ZERO(&mask);      //Initialze to 0
  CPU_SET(1, &mask);    //set to desired core
  sched_setaffinity(0,sizeof(cpu_set_t), &mask);    //set affinity of process to defined mask

  if(pipe(pp) < 0 || pipe(cp) < 0)  //check for error when creating pipes
    return 1;

  pid = fork();

  if(pid < 0) //check if fork failed
    return 1;

  else if (pid > 0) //parent process
  {
    for(i = 0; i < SAMPLE_SIZE; i++)
    {
      clock_gettime(CLOCK_MONOTONIC, &start);
      write(pp[1], start.tv_nsec, sizeof(start.tv_nsec));
      read(cp[0], &time_stmp, sizeof(time_stmp));
      printf("%.08f\n", fabs(time_stmp - start.tv_nsec);
    }
  }

  else  //child process
  {
    for(i = 0; i < SAMPLE_SIZE; i++)
    {
      clock_gettime(CLOCK_MONOTONIC, &start);
      write(cp[1], start.tv_nsec, sizeof(start.tv_nsec));
      read(pp[0], time_stmp, sizeof(time_stmp));
      printf("%.08f\n", fabs(time_stmp - start.tv_nsec));
    }
  }

  return 0;
}
