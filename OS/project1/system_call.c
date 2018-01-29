/**********************************************************

 system_call.c : measures the time it takes to do system call
 Scott De Silva & Shaughn Seepaul

**********************************************************/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#define SAMPLE_SIZE 50

int main()
{
  long sum = 0, delta = 0, average = 0;
  struct timespec start, end;


  char data[0];

  int file_dscr = open("test.txt", O_CREAT | O_RDONLY, S_IRUSR);  //open/create file

  if(file_dscr < 0) //error
    return 1;

  // if(read(file_dscr, data, 0) < 0)
  //   return 1;

  for(int i = 0; i < SAMPLE_SIZE; i++)
  {
    clock_gettime(CLOCK_MONOTONIC, &start);
    read(file_dscr,data,0);
    clock_gettime(CLOCK_MONOTONIC, &end);

    delta = end.tv_nsec - start.tv_nsec;
    printf(" %d %li\n", i,delta);
    sum += delta;
  }

  if(close(file_dscr) < 0)
    return 1;

  average = sum/SAMPLE_SIZE;

  printf("%.03li nanoseconds\n", average);

//may want to remove file after operation to clean up

  return 0;
}
