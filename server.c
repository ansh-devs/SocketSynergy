/* server.c */  
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int sockfd =-1,ret=-1, sessionfd=-1;
  char rbuf[20];
  struct sockaddr_in serv_addr, cli_addr;
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  
  if (sockfd < 0) {
    perror("Error opening socket connection !");
    return EXIT_FAILURE;
  }

  printf("Socket created successfully\n");
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080); // Serving Port
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP Address
  
  ret = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  
  if (ret < 0) {
    perror("error binding");
    close(sockfd);
    return -1;
  }

  printf("Server:: Bind success %s:%d\n", inet_ntoa(serv_addr.sin_addr),ntohs(serv_addr.sin_port));  

  ret = listen(sockfd,5);
  if (ret < 0) {
    perror("Failed at listening for the connections");
    close(sockfd);
    return EXIT_FAILURE;
  }

  printf("Server:: Listening for upcoming connections\n");
  int len;
  len = sizeof(cli_addr);
  sessionfd = accept(sockfd, (struct sockaddr *)&cli_addr,&len);
  if (sessionfd < 0) {
    perror("Accept failed");
    close(sockfd);
    return EXIT_FAILURE;
  }

  printf("Server:: Accepted connection from %s:%hd\n",
         inet_ntoa(cli_addr.sin_addr),
         ntohs(cli_addr.sin_port));
  
  /*
   * Communication between server & client will happen here...
   */

  read(sessionfd,rbuf,sizeof(rbuf));
  
  printf("Server:: data from the client is %s \n",rbuf);

  write(sessionfd,rbuf,strlen(rbuf)+1);
  printf("Server:: sended data to client\n");

  printf("Server:: closing session with the client\n");
  close(sessionfd);
  
  printf("Server:: gracefully shutting down server\n");
  close(sockfd);
  return EXIT_SUCCESS;
}
