#include "tlpi_hdr.h"
#include <stdio.h>

static int iData = 0;
int main(int argc, char const *argv[]) {
  int iLocal = 100;

  pid_t childPid;

  switch(childPid = fork()) {
    case -1:
      printf("Error!!!\n");
      return -1;
      break;

    case 0:
      iData++;
      iLocal++;
      break;

    default:
      sleep(3);
      break;
  }

  printf("PID=%ld %s  iData=%d iLocal=%d\n", (long)getpid(), (0==childPid?"(child)":"(parent)", iData, iLocal));

  return 0;
}
