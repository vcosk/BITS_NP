
#include "tlpi_hdr.h"

int main(int argc, char const *argv[]) {
  if(argc < 2) {
    printf("usage format %s command ... \n", argv[0]);
  }
  else {
    int limit = 1;
    char *params[argc - limit + 1];
    int index;
    for(index=0; index<(argc - limit); index++) {
      params[index] = (char *)malloc(strlen(argv[index+limit])+1);
      strcpy(params[index], argv[index+limit]);
      printf("%s\n", params[index]);
    }
    params[index] = NULL;
    execvp(params[0], params);
  }

  return 0;
}
