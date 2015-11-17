#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MESSAGE_BUFFER_SIZE 512

char *mip;
int mport;
int chPid;
void signalHandler(int);
void messageTransmitter(char*, int, pid_t);

int main(int argc, char *argv[])
{
    struct sockaddr_in addr;
    int fd, nbytes,addrlen;
    struct ip_mreq mreq;
    char msgbuf[MESSAGE_BUFFER_SIZE];

    pid_t currentPID = getpid();
    char pidStr[15];
    sprintf(pidStr,"%d",currentPID);
    printf("Parent PID: %d\n", currentPID);
    if(argc != 3)
    {
        printf("correct usage: a.out <mlticast IP> <port>\n");
        exit(1);
    }
    char *ip = argv[1];
    int port = atoi(argv[2]);
    mip = ip;
    mport = port;


    u_int yes=1;

    if ((fd=socket(PF_INET,SOCK_DGRAM,0)) < 0) {
        perror("socket");
        exit(1);
    }


    /* allow multiple sockets to use the same PORT number */
    if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) {
        perror("Reusing ADDR failed");
        exit(1);
    }

    /* set up destination address */
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    addr.sin_port=htons(port);

    /* bind to receive address */
    if (bind(fd,(struct sockaddr *) &addr,sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    /* use setsockopt() to request that the kernel join a multicast group */
    mreq.imr_multiaddr.s_addr=inet_addr(ip);
    mreq.imr_interface.s_addr=htonl(INADDR_ANY);
    if (setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0) {
        perror("setsockopt mreq");
        exit(1);
    }

    pid_t childpid;
    int retval;
    int status;

    childpid = fork();
    if (childpid >= 0) /* fork succeeded */
    {
        if (childpid == 0)        {
            messageTransmitter(ip, port, currentPID);
        }
        else
        {
            chPid = childpid;
            signal(SIGINT, signalHandler);
            char from_ip[20] = {0};
            /* now just enter a read-print loop */
            while (1) {
                addrlen=sizeof(addr);
                memset(msgbuf,0,MESSAGE_BUFFER_SIZE);
                if ((nbytes=recvfrom(fd,msgbuf,MESSAGE_BUFFER_SIZE,0,
                                (struct sockaddr *) &addr,&addrlen)) < 0) {
                    perror("recvfrom");
                    exit(1);
                }
                else
                {
                    printf("Receive\n");
                    inet_ntop(AF_INET, &addr.sin_addr, from_ip, sizeof(from_ip));
                    if(strstr(msgbuf, pidStr) == NULL) {
                      printf("%s : %s : My PID: %s\n",from_ip, msgbuf, pidStr);
                    }
                }
            }
        }
    }
    else
    {
        perror("fork");
        exit(0);
    }
}


void messageTransmitter(char *ip, int port, pid_t srcPID)
{
    struct sockaddr_in addr;
    int fd;
    char message[MESSAGE_BUFFER_SIZE];

    /* create what looks like an ordinary UDP socket */
    if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
        perror("socket");
        exit(1);
    }

    /* set up destination address */
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(port);

    /* now just sendto() our destination! */
    while (1) {
        time_t t = time(0);
        printf("Send\n");
        sprintf(message, "Hello-%-24.24s-%d", ctime(&t),srcPID);
        if (sendto(fd,message,strlen(message),0,(struct sockaddr *) &addr,
                    sizeof(addr)) < 0) {
            perror("sendto");
            exit(1);
        }
        sleep(15);
    }
}

void signalHandler(int sig)
{
    kill(chPid, SIGTERM);
    struct sockaddr_in addr;
    int fd;
    char message[MESSAGE_BUFFER_SIZE];

    if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
        perror("socket");
        exit(1);
    }

    /* set up destination address */
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(mip);
    addr.sin_port=htons(mport);

    time_t t = time(0);
    sprintf(message, "Bye-%-24.24s", ctime(&t));
    if (sendto(fd,message,strlen(message),0,(struct sockaddr *) &addr,
                sizeof(addr)) < 0) {
        perror("sendto");
        exit(1);
    }
    exit(1);
}
