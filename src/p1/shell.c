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

  while (error == 0 && bContinueLoop) {
    //Print shell prompt
    printf("prompt$: ");
    //Reads the input data from stdin and copies to sCommand string.
    if (fgets(sCommand, sizeof sCommand, stdin)) {
      //Removes the new line charecter from the end.
      sCommand[(strlen(sCommand)) - 1] = '\0';
      //If text is entered.
      if(strlen(sCommand) > 0) {
        trim(sCommand);

        loop_pipe(sCommand);
        // char **sCommandPipeSplit = NULL;
        // int iPipeSplitSize = split(sCommand, '|', &sCommandPipeSplit);
        // char **sSplitStr = NULL;
        // int iSplitSize = split(sCommand, ' ', &sSplitStr);
        // if(iSplitSize > 0) {
        //   if(strcmp(sSplitStr[0], "exit") == 0 || strcmp(sSplitStr[0], "x") == 0 || strcmp(sSplitStr[0], "q") == 0) {
        //     bContinueLoop = FALSE;
        //     break;
        //   }
        //   else {
        //   }
        // printf("iPipeSplitSize: %d\n", iPipeSplitSize);
        // for(int iPipeIndex=0; iPipeIndex < iPipeSplitSize; iPipeIndex++) {
        //   trim(sCommandPipeSplit[iPipeIndex]);
        //   printf("sCommandPipeSplit[iPipeIndex]: %s\n", sCommandPipeSplit[iPipeIndex]);
        //   char **sCommandArgSplit = NULL;
        //   int iArgSplitSize = split(sCommandPipeSplit[iPipeIndex], ' ', &sCommandArgSplit);
        //   printf("iArgSplitSize: %d\n", iArgSplitSize);
        //   int bLastCommand = (iPipeIndex+1) == iPipeSplitSize?TRUE:FALSE;
        //   for(int iArgIndex=0; iArgIndex < iArgSplitSize; iArgIndex++) {
        //     printf("%s\n", sCommandArgSplit[iArgIndex]);
        //     if(bLastCommand) {
        //       printf("I AM THE LAST ONE!!!\n");
        //     }
        //   }
        // }
        // }
      }
    }
  }
  return 0;
}

void    loop_pipe(char *sCommand)
{

  trim(sCommand);
  char **sCommandPipeSplit = NULL;
  printf("sCommand: %s\n", sCommand);
  int iPipeSplitSize = split(sCommand, '|', &sCommandPipeSplit);


  int iCharCount = 0;
  int iRedirectCount = 0;
  for(int iPipeIndex=0; iPipeIndex < iPipeSplitSize; iPipeIndex++) {
    int iCurrentCommandStrLen = strlen(sCommandPipeSplit[iPipeIndex]);
    if(iCurrentCommandStrLen == 0) {
      iCharCount += (iPipeIndex-1);
      while(sCommand[iCharCount + iRedirectCount] == '|') {
        iRedirectCount++;
      }
      sCommandPipeSplit[iPipeIndex] = NULL;
      iPipeSplitSize = iPipeIndex;
      break;
    }
    iCharCount += iCurrentCommandStrLen;
  }

  char **sRedirctCommands = NULL;
  int iRedirectCommandCount = split(&sCommand[iCharCount + iRedirectCount], ',', &sRedirctCommands);


  int   p[2];
  pid_t pid;
  int   fd_in = 0;

  for(int iPipeIndex=0; iPipeIndex < iPipeSplitSize; iPipeIndex++) {
    int bLastCommand = (iPipeIndex+1) == iPipeSplitSize?TRUE:FALSE;
    char **sCommandArgSplit = NULL;
    trim(sCommandPipeSplit[iPipeIndex]);
    int iArgSplitSize = split(sCommandPipeSplit[iPipeIndex], ' ', &sCommandArgSplit);
    pipe(p);
    if ((pid = fork()) == -1)
    {
      exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
      dup2(fd_in, 0); //change the input according to the old one
      if (!bLastCommand) {
        dup2(p[1], 1);
      }
      close(p[0]);
      execvp(sCommandArgSplit[0], sCommandArgSplit);
      exit(EXIT_FAILURE);
    }
    else
    {
      wait(NULL);
      close(p[1]);
      fd_in = p[0]; //save the input for the next command
    }
  }
}

void executeCommandOnePipe(char **sCommand, int command_pipe[]) {
  pid_t childpid;
  printf("debug1\n");
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
      printf("debug2\n");
      if(dup2(STDIN_FILENO, command_pipe[0]) == -1) {
        errExit("Child: Error replacing STDIN_FILENO");
      }

      if(dup2(STDOUT_FILENO, command_pipe[1]) == -1) {
        errExit("Child: Error replacing STDOUT_FILENO");
      }

      if(dup2(STDERR_FILENO, command_pipe[1]) == -1) {
        errExit("Child: Error replacing STDOUT_FILENO");
      }

      printf("debug3\n");
      // sleep(5);
      execvp(sCommand[0], sCommand);
      errExit("Invalid command %s", sCommand[0]);
      break;
      //Waits till the child precess executes the command.
    default:
      wait(0);
      // sleep(5);
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
