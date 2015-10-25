#include "tlpi_hdr.h"

int main(int argc, char const *argv[]) {
  int command_pipe[2];
  if(pipe(command_pipe) == -1) {
    perror("Pipe failed");
    exit(1);
  }

  int command_pipe_2[2];
  if(pipe(command_pipe_2) == -1) {
    perror("Pipe failed");
    exit(1);
  }

  char* prog1[] = { "ls", "-l", 0};
  char* prog2[] = { "wc", "-l", 0};
  char* prog3[] = { "wc", "-c", 0};
  executeCommand(command_pipe, prog1, TRUE);
  wait(0);
  read_all(command_pipe[0],command_pipe_2[1]);
  // close(command_pipe[0]);
  // close(command_pipe[1]);
  executeCommand(command_pipe_2, prog2, TRUE);
  executeCommand(command_pipe_2, prog3, FALSE);
  wait(0);
  wait(0);
  close(command_pipe_2[0]);
  close(command_pipe_2[1]);
  return 0;
}

void executeCommand(int command_pipe[], char* prog[], int closeStdOut) {
  if(fork() == 0)        //first fork
  {
    close(0);          //closing stdin
    dup(command_pipe[0]);     //replacing stdin with pipe read
    if(closeStdOut) {
      close(1);          //closing stdout
      dup(command_pipe[1]);     //replacing stdout with pipe write
    }
    close(command_pipe[0]);   //closing pipe read
    close(command_pipe[1]);

    execvp(prog[0], prog);
    perror("execvp of ls failed");
    exit(1);
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
