
#include "tlpi_hdr.h"

int main(int argc, char const *argv[]) {

  if(argc < 2) {
    printf("usage format %s command ... \n", argv[0]);
  }
  else {
    // execlp("ls", "ls", "-lrt", (char *)0);

    // execlp(argv[1], argv[1], (char *)0);
    // execlp(argv[1], argv[1], *(argv+2), (char *)0);

    if(argc > 2) {
      char *params[10];
      int index;
      for(index=0; index<(argc - 2); index++) {
        params[index] = (char *)malloc(strlen(argv[index+2])+1);
        strcpy(params[index], argv[index+2]);
        // printf("%s\n", params[index]);
      }
      execvp(argv[1], params);
    }
  }

  return 0;
}
