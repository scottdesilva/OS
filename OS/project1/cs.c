/**********************************************************

 context_switch.c : measures the time between a context switch
 Scott De Silva & Shaughn Seepaul

**********************************************************/
#define _GNU_SOURCE
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
  double time_stmp, delta, sum;
  struct timespec start, end;


  cpu_set_t mask;       //define bit mask
  CPU_ZERO(&mask);      //Initialze to 0
  CPU_SET(1, &mask);    //set to desired core
  sched_setaffinity(0,sizeof(cpu_set_t), &mask);    //set affinity of process to defined mask

  if(pipe(pp) < 0 || pipe(cp) < 0)  //check for error when creating pipes
    return 1;

  pid = fork();

//  struct timespec start, end;     //TRY THIS


  if(pid < 0) //check if fork failed
    return 1;

  else if (pid > 0) //parent process
  {
    for(i = 0; i < SAMPLE_SIZE; i++)
    {
      clock_gettime(CLOCK_MONOTONIC, &start);

      printf("start: %f\n", start.tv_nsec); //may have to make ld not f

      write(pp[1], &start.tv_nsec, sizeof(start.tv_nsec));
      read(cp[0], &time_stmp, sizeof(time_stmp));

      printf("stamp: %f\n", time_stmp);

      delta = fabs(time_stmp - start.tv_nsec);
      sum += delta;

  //    write(pp[1], &start.tv_nsec, sizeof(start.tv_nsec));        //force
  //    read(cp[0], &time_stmp, sizeof(time_stmp));                 //force
    }
  }

  else  //child process
  {
    for(i = 0; i < SAMPLE_SIZE; i++)
    {
      clock_gettime(CLOCK_MONOTONIC, &end);

      printf("end: %f\n", end.tv_nsec); //may have to change f to ld

      write(cp[1], &end.tv_nsec, sizeof(end.tv_nsec));
      read(pp[0], &time_stmp, sizeof(time_stmp));

      delta = fabs(time_stmp - end.tv_nsec);
      sum += delta;

  //    write(cp[1], &start.tv_nsec, sizeof(start.tv_nsec));    //force
  //    read(pp[0], &time_stmp, sizeof(time_stmp));             //force
    }
  }

  printf("%f\n", sum/SAMPLE_SIZE);
  return 0;
}
