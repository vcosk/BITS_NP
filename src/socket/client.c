#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(char*);

void error(char *msg)
{
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[])
{
  int sockfd, portno;
  struct sockaddr_in servr_addr;
  struct hostent *server;

  char buff[256];

  if(argc < 3) {
    error("Pass ip address and port as  arguments\n");
  }

  portno = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    error("Error creating socket\n");
  }

  server = gethostbyname(argv[1]);
  if(server == NULL) {
    error("No such host\n");
  }

  bzero((char *) &servr_addr, sizeof(servr_addr));

  servr_addr.sin_family = AF_INET;
  bcopy((char*)server->h_addr, (char *)&servr_addr.sin_addr.s_addr, server->h_length);
  servr_addr.sin_port = htons(portno);

  if(connect(sockfd, (struct sockaddr *) &servr_addr, sizeof(servr_addr)) < 0) {
    error("Unable to connect\n");
  }

  printf("Enter a message: ");
  bzero(buff, 255);
  fgets(buff, 255, stdin);

  int n = write(sockfd, buff, strlen(buff));
  if(n < 0) {
    error("Unable to send message.\n");
  }

  bzero(buff, 255);
  n = read(sockfd, buff, 255);

  if(n < 0) {
    error("No response from server.\n");
  }

  printf("%s\n", buff);

}
