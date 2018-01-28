/**********************************************************

 system_call.c : measures the time it takes to do system call
 Scott De Silva & Shaughn Seepaul

**********************************************************/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

int main()
{
  int time_stmp;
  // char data[0];
  //
  // int file_dscr = open("test.txt", O_CREAT | O_RDONLY, S_IRUSR);  //open/create file
  //
  // if(file_dscr < 0) //error
  //   return 1;
  //
  // if(read(file_dscr, data, 0) < 0)
  //   return 1;
  //
  // if(close(file_dscr) < 0)
  //   return 1;

  

  printf("Success\n");

//may want to remove file after operation to clean up

  return 0;
}
