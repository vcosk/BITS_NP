#include "rshmAPI.h"

int shmidArray[100];
int idArrayLength = 0;

int rshmget(key_t key, size_t size) {

  int shmid;
  if ((shmid = shmget(key, size, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
  }

  shmidArray

}

void rshmat(int rshmid, void* addr) {

}

int rshmdt(int rshmid, void* addr) {

}

int rshmctl(int rshmid, int cmd) {

}

void rshmChanged(int rshmid) {

}

int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
