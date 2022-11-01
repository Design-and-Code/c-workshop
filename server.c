#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <string.h>
#include <strings.h>

#define SIZE 1024
#define STD_IN 0

void communicate(int fd)
{
  char buff[SIZE];
  while(1)
  {
    bzero(buff,SIZE);
    read(fd,buff,SIZE);
    printf("Client Sent : %s",buff);
    printf("Sent a response \n");
    read(STD_IN,buff,SIZE);
    write(fd,buff,SIZE);
    if(strncmp("exit",buff,4) == 0)
    {
      printf("Exit...");
      break;
    }
  }
}


int main()
{
  int server_file_descriptor, connection_file_descriptor;
  struct sockaddr_in server, client;
   
  //create socket
  server_file_descriptor = socket(AF_INET,SOCK_STREAM,0);
  if(server_file_descriptor == -1)
  {
    perror("Failes to create socket");
    exit(1);
  }
  else
  {
    printf("Socket created successfully ...");
  }

  //Socket configuration
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(8080);

  //Binding
  if(bind(server_file_descriptor,(struct sockaddr *)&server,sizeof(server)) == 0)
  {
    printf("\nBinding successful...");
  }
  else
  {
    perror("Bind failed");
    exit(1);
  }

  if(listen(server_file_descriptor,5) == 0)
  {
    printf("\nListening..,");
  }
  else
  {
    perror("\nListening failed...");
    exit(1);
  }

  //Accepting connections
  int size = sizeof(client);
  connection_file_descriptor = accept(server_file_descriptor,(struct sockaddr *)&client,&size);
  if(connection_file_descriptor < 0)
  {
    perror("Connection failed..\n");
    exit(1);
  }
  else
  {
    printf("Connected..\n");
  }

  communicate(connection_file_descriptor);

  close(server_file_descriptor);
  return 0;
}
