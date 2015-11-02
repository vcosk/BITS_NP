#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(char*);

void error(char *msg)
{
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[])
{
  int sockfd, newsockfd, clientln, portno;
  char buff[256];

  struct sockaddr_in servr_addr, client_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if(argc < 2) {
    error("Port number needs to be specified.\n");
  }

  if(sockfd < 0) {
    error("Error creating socket.");
  }

  bzero((char *) &servr_addr, sizeof(servr_addr));

  portno = atoi(argv[1]);

  servr_addr.sin_family = AF_INET;
  servr_addr.sin_addr.s_addr = INADDR_ANY;
  servr_addr.sin_port = htons(portno);

  if(bind(sockfd, (struct sockaddr*) &servr_addr, sizeof(servr_addr)) < 0) {
    error("Error in binding.\n");
  }

  //Maximum 5 clients
  listen(sockfd, 5);
  clientln = sizeof(client_addr);
printf("HELLO\n");
  newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &clientln);
  printf("HELLO1\n");
  if(newsockfd < 0) {
    error("Error on accept\n");
  }

  bzero(buff, 256);

  int n = read(newsockfd, buff, 255);

  if(n < 0) {
    error("Error reading scoket\n");
  }

  printf("This was the message: %s\n", buff);

  n = write(newsockfd, "Receive msg!!!", 14);

  if(n < 0) {
    error("Unavel to send response\n");
  }

  return 0;

}
