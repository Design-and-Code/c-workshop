#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
  pid_t pid;
  pid_t pid2; 

  pid = fork();
  // pid2 = fork();
 
  if(pid == -1)
  {
    perror("Can't create child process \n");
    exit(1);
  }

  if(pid == 0)
  {
    printf("Hello There \n");
    int i=0;
    for(i;i<10;i++)
      {
        printf("%d \n",i);
      }
  }
  else
  {
    wait(NULL);
    printf("Goodbye \n");
  }
}
