/* client.c */
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

int main (void)
{
  int sockfd = -1,ret = -1;
  struct sockaddr_in serv_addr;
  char buf[20];
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if (sockfd < 0){
    perror("failed at creating socket");
    return EXIT_FAILURE;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  ret = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  if (ret < 0){
    perror("connection failed to the server\n");
    close(sockfd);
    return EXIT_FAILURE;
  }
  
  printf("Connection established with the server\n");

  /*
   * Communication with the server initiating the req.
   */

  strncpy(buf,"Hey",6);
  write(sockfd,buf,strlen(buf)+1);
  printf("data written to the server\n");

  memset(buf, '\0', sizeof(buf));
  // Read the msg from the server.
  read(sockfd,buf,sizeof(buf));
  printf("data read from the server %s\n",buf);

  close(sockfd);
  return EXIT_SUCCESS;


}

