#include "tlpi_hdr.h"

#define  MAX_COMMAND_STRING_SIZE 256
#define BUF_SIZE 10

void trim(char *);
int split (const char*, char, char***);
void executeCommandOnePipe(char**, int[]);

static int error = 0;

int main(int argc, char *argv[]) {
  char sCommand[MAX_COMMAND_STRING_SIZE];
  int bContinueLoop = TRUE;

  //Pipe to be used
  int command_pipe[2];
  if (pipe(command_pipe) == -1) {
    errExit("pipe"); /* Create the pipe */
  }


  while (error == 0 && bContinueLoop) {
    //Print shell prompt
    printf("VIKK: ");
    //Reads the input data from stdin and copies to sCommand string.
    if (fgets(sCommand, sizeof sCommand, stdin)) {
      //Removes the new line charecter from the end.
      sCommand[(strlen(sCommand)) - 1] = '\0';
      //If text is entered.
      if(strlen(sCommand) > 0) {
        trim(sCommand);

        char **sSplitStr = NULL;
        int iSplitSize = split(sCommand, ' ', &sSplitStr);
        if(iSplitSize > 0) {
          if(strcmp(sSplitStr[0], "exit") == 0) {
            bContinueLoop = FALSE;
            break;
          }
          else if(strcmp(sSplitStr[0], "x") == 0) {
            bContinueLoop = FALSE;
            break;
          }
          else {
            executeCommandOnePipe(sSplitStr, command_pipe);
          }
        }

        char* prog2[] = { "wc", "-l", NULL};
        executeCommandOnePipe(prog2, command_pipe);

        read_all(command_pipe[0], STDOUT_FILENO);


        // char buf[BUF_SIZE];
        // ssize_t numRead;
        //
        // for (;;) {
        //   printf("PP\n");
        //   /* Read data from pipe, echo on stdout */
        //   numRead = read(command_pipe[0], buf, BUF_SIZE);
        //   if (numRead == -1) {
        //     errExit("read");
        //   }
        //   if (numRead == 0) {
        //     break;
        //   }
        //   /* End-of-file */
        //   if (write(STDOUT_FILENO, buf, numRead) != numRead) {
        //     fatal("parent - partial/failed write");
        //   }
        // }
      }
    }
  }
  return 0;
}

void executeCommandOnePipe(char **sCommand, int command_pipe[]) {
  pid_t childpid;
  childpid = fork();
  switch (childpid) {
    case -1:
      errExit("executeCommand: Error in fork");
      break;
    case 0:
      if(close(command_pipe[0]) == -1) {
        errExit("Child: Error closing pipe read");
      }

      if(close(command_pipe[1]) == -1) {
        errExit("Child: Error closing pipe write");
      }

      if(dup2(STDIN_FILENO, command_pipe[0]) == -1) {
        errExit("Child: Error replacing STDIN_FILENO");
      }

      if(dup2(STDOUT_FILENO, command_pipe[1]) == -1) {
        errExit("Child: Error replacing STDOUT_FILENO");
      }

      execvp(sCommand[0], sCommand);
      break;
      //Waits till the child precess executes the command.
    default:
      wait(0);
      sleep(10);
      if(close(command_pipe[0]) == -1) {
        errExit("Parent: Error closing pipe read");
      }

      if(close(command_pipe[1]) == -1) {
        errExit("Parent: Error closing pipe write");
      }
      break;
  }
}

void read_all(int src, int dst) {
  char buf[BUFSIZ];
  ssize_t bytes_read, bytes_written;
  while((bytes_read = read(src, buf, BUFSIZ)) > 0) {
    bytes_written = 0;
    while(bytes_written < bytes_read)
      bytes_written += write(dst,
        buf + bytes_written,
        bytes_read - bytes_written);
  }
}

int split (const char *str, char c, char ***arr) {
    int count = 1;
    int token_len = 1;
    int i = 0;
    char *p;
    char *t;

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
            count++;
        p++;
    }

    *arr = (char**) malloc(sizeof(char*) * count);
    if (*arr == NULL)
        exit(1);

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
        {
            (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
            if ((*arr)[i] == NULL)
                exit(1);

            token_len = 0;
            i++;
        }
        p++;
        token_len++;
    }
    (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
    if ((*arr)[i] == NULL)
        exit(1);

    i = 0;
    p = str;
    t = ((*arr)[i]);
    while (*p != '\0')
    {
        if (*p != c && *p != '\0')
        {
            *t = *p;
            t++;
        }
        else
        {
            *t = '\0';
            i++;
            t = ((*arr)[i]);
        }
        p++;
    }

    return count;
}

/*
 * Function removes the leading and trailing space from the string.
 */
void trim(char *str)
{
    int i;
    int begin = 0;
    int end = strlen(str) - 1;

    while (isspace(str[begin]))
        begin++;

    while ((end >= begin) && isspace(str[end]))
        end--;

    // Shift all characters back to the start of the string array.
    for (i = begin; i <= end; i++)
        str[i - begin] = str[i];

    str[i - begin] = '\0'; // Null terminate string.
}
