/* server.c */  
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
  int sockfd =-1,ret=-1;
  struct sockaddr_in serv_addr;
  sockfd=socket(AF_INET,SOCK_STREAM,0);
 
  if (sockfd < 0) {
    perror("Error opening socket connection !");
    return EXIT_FAILURE;
  }
  printf("Socket created successfully\n");
  
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080); /* Serving Port */
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); /* IP Address */
  
  ret = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  
  if (ret < 0) {
    perror("error binding");
    close(sockfd);
    return -1;
  }
  
  printf("Bind success %s:%d\n", inet_ntoa(serv_addr.sin_addr),ntohs(serv_addr.sin_port));

  close(sockfd);
  return EXIT_SUCCESS;
}
