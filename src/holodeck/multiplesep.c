#include "tlpi_hdr.h"

int split (const char*, char, char***);

int main(int argc, char const *argv[]) {

  char *sCommand = "ls|cat||wc,grep";
  char **sCommandPipeSplit = NULL;

  printf("%s\n", sCommand);
  printf("%s\n", sCommand[1]);
  trim(&sCommand);

  int iPipeSplitSize = split(sCommand,'|',&sCommandPipeSplit);
  printf("iPipeSplitSize: %d\n", iPipeSplitSize);
  int iCharCount = 0;
  int iRedirectCount = 0;
  for(int iPipeIndex=0; iPipeIndex < iPipeSplitSize; iPipeIndex++) {
    int iCurrentCommandStrLen = strlen(sCommandPipeSplit[iPipeIndex]);
    if(iCurrentCommandStrLen == 0) {
      iCharCount += (iPipeIndex-1);
      printf("Multidirect pipe starts : %d\n", iCharCount);
      printf("%c\n", sCommand[iCharCount]);
      printf("%s\n", &(sCommand[iCharCount]));
      while(sCommand[iCharCount + iRedirectCount] == '|') {
        iRedirectCount++;
      }
      sCommandPipeSplit[iPipeIndex] = NULL;
      iPipeSplitSize = iPipeIndex;
      break;
    }
    iCharCount += iCurrentCommandStrLen;
  }

  printf("iRedirectCount: %d\n", iRedirectCount);
  char **sRedirctCommands = NULL;
  printf("iCharCount + iRedirectCount: %d\n", (iCharCount + iRedirectCount));
  int iRedirectCommandCount = split(&sCommand[iCharCount + iRedirectCount], ',', &sRedirctCommands);
  printf("iRedirectCommandCount: %d\n", iRedirectCommandCount);

  for(int iRedirectCommandIndex=0; iRedirectCommandIndex < iRedirectCommandCount; iRedirectCommandIndex++) {
    printf("%s\n", sRedirctCommands[iRedirectCommandIndex]);
  }

  for(int iPipeIndex=0; iPipeIndex < iPipeSplitSize; iPipeIndex++) {
    trim(sCommandPipeSplit[iPipeIndex]);
    printf("sCommandPipeSplit[iPipeIndex]: %s\n", sCommandPipeSplit[iPipeIndex]);
  }

  return 0;
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
