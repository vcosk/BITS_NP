#include <stdio.h>

int main(int argc, char *argv[]) {

  int iArgIndex = 0;

  printf("Hello World!!!\n  ");

  printf("Argument size: %d\n", argc);

  if(argc > 0) {
    for(iArgIndex=0; iArgIndex < argc; iArgIndex++) {
      printf("Argument #%d is %s\n", (iArgIndex+1), argv[iArgIndex]);
    }
  }

return 0;
}
