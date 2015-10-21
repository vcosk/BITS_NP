
#include "tlpi_hdr.h"

int main(int argc, char const *argv[]) {
  // if(argc < 2) {
  //   printf("usage format %s command ... \n", argv[0]);
  // }
  // else {
  //   int limit = 1;
  //   char *params[argc - limit + 1];
  //   int index;
  //   for(index=0; index<(argc - limit); index++) {
  //     params[index] = (char *)malloc(strlen(argv[index+limit])+1);
  //     strcpy(params[index], argv[index+limit]);
  //     printf("%s\n", params[index]);
  //   }
  //   params[index] = NULL;
  //   execvp(params[0], params);
  // }
  //
  // return 0;

  int des_p[2];
        if(pipe(des_p) == -1) {
          perror("Pipe failed");
          exit(1);
        }

        if(fork() == 0)        //first fork
        {
            close(1);          //closing stdout
            dup(des_p[1]);     //replacing stdout with pipe write
            close(des_p[0]);   //closing pipe read
            close(des_p[1]);

            const char* prog1[] = { "ls", "-l", 0};
            execvp(prog1[0], prog1);
            perror("execvp of ls failed");
            exit(1);
        }

        if(fork() == 0)        //creating 2nd child
        {
            close(0);          //closing stdin
            dup(des_p[0]);     //replacing stdin with pipe read
            close(des_p[1]);   //closing pipe write
            close(des_p[0]);

            const char* prog2[] = { "wc", "-l", 0};
            execvp(prog2[0], prog2);
            perror("execvp of wc failed");
            exit(1);
        }

        // close(des_p[0]);
        close(des_p[1]);
        wait(0);
        wait(0);

        return 0;
}
