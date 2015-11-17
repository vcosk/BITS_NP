#include "tlpi_hdr.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define EXAMPLE_PORT 6000
#define EXAMPLE_GROUP "239.0.0.1"

void error(char *msg) {
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[]) {

  if(argc != 3) {
    error("Usage: multicast <GROUP_IP> <PORT_NUM>\n");
  }

  struct sockaddr_in addr;
  int addrlen, sock, cnt;
  struct ip_mreq mreq;
  char message[50];

  int port = atoi(argv[2]);
  char *ip;

  strcpy(ip, argv[1]);

   /* set up socket */
   sock = socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) {
     perror("unable to create socket\n");
     exit(1);
   }

   u_int yes=1;
   if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) {
        perror("unable to reuse ports");
        exit(1);
   }
   bzero((char *)&addr, sizeof(addr));

   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   addr.sin_port = htons(port);
   addrlen = sizeof(addr);

  int mainPID;
  int pingPID;
  int waitPid;
  switch((mainPID = fork())) {
    case -1:
      error("Error in forking\n");
      break;
    case 0:
      while(TRUE) {
        switch((pingPID = fork())) {
          case -1:
            error("Error in forking\n");
            break;
          case 0:
            printf("%u\n", (unsigned)time(NULL));
            switch((waitPid = fork())) {
              case -1:
                error("Error in forking\n");
                break;
              case 0:
                sleep(5);
                printf("waiting\n");
                break;
              default:
                wait(NULL);
                break;
            }
            exit(0);
            break;
          default:
            wait(NULL);
            sleep(15);
            break;
        }
      }
      break;
      default:
          while(TRUE) {
          /* receive */
          if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
             error("Binding error\n");
          }
          mreq.imr_multiaddr.s_addr = inet_addr(EXAMPLE_GROUP);
          mreq.imr_interface.s_addr = htonl(INADDR_ANY);
          if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,
             &mreq, sizeof(mreq)) < 0) {
               error("setsockopt mreq\n");
          }
        }
        break;
    }



  return 0;
}
