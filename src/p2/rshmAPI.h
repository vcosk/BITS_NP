#include "tlpi_hdr.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#ifndef 

int rshmget(key_t, size_t);
void rshmat(int, void*);
int rshmdt(int, void*);
int rshmctl(int, int);
void rshmChanged(int);

struct rshminfo{
int rshmid;
/*unique id across all systems. created by the
first system*/
key_t key;
/*key used to create shm segment*/
int shmid;
/*shmid returned by the local system*/
void *addr;
/*address returned by the local system*/
int ref_count;
/*no of processes attached to*/
struct sockaddr_in *remote_addrs; /* list of remote end
points*/
};
