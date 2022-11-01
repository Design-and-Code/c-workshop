#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  int file_descriptor;
  char buf[14];

  file_descriptor = open("demo.txt",O_CREAT | O_RDWR);

  if(file_descriptor == -1)
  {
    perror("Failed to create/open a file");
    exit(1);
  }

  write(file_descriptor,"Hello World!\n",13);

  close(file_descriptor);

  // read
  file_descriptor = open("demo.txt",O_RDONLY);
  
  if(file_descriptor == -1)
  {
    perror("Failed to read the file");
    exit(1);
  }

  read(file_descriptor,buf,13);

  write(1,buf,13);

  close(file_descriptor);

}
