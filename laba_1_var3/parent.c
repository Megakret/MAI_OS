#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
const size_t BUFFER = 100;
int main() {
  int err = printf("Write a file path(absolute path) for a child process: ");
  if (err < 0) {
    printf("Error: %s\n", strerror(errno));
    return -1;
  }
  char child_name[BUFFER];
  char *s = fgets(child_name, BUFFER, stdin);
  if (s == NULL) {
    fprintf(stderr, "Error: %s\n\n", strerror(errno));
    return -1;
  }
  // Removing \n from filepath
  for (int i = 0; i < BUFFER; i++) {
    if (s[i] == '\n') {
      s[i] = '\0';
      break;
    }
  }
  int input_pipe[2];
  err = pipe(input_pipe);
  if (err == -1) {
    fprintf(stderr, "Error: %s\n", strerror(errno));
    return -1;
  }
  int pid = fork();
  if (pid == 0) {
    // child
    // replacing stdin
    int err = dup2(input_pipe[0], STDIN_FILENO);
    if (err == -1) {
      fprintf(stderr, "Error: %s\n", strerror(errno));
      return -1;
    }
    err = close(input_pipe[1]);
    if (err == -1) {
      fprintf(stderr, "Error: %s\n", strerror(errno));
      return -1;
    }
    err = execl(child_name, child_name, (char *)NULL);
    if (err == -1) {
      fprintf(stderr, "Error: %s\n", strerror(errno));
      return -1;
    }
    return -1;
  } else if (pid == -1) {
    // error
    return -1;
  } else {
    // parent
    char c;
    while ((c = getchar()) != EOF) {
      err = write(input_pipe[1], &c, sizeof(char));
      if (err == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return -1;
      }
    }
    int err = close(input_pipe[1]);
    if (err == -1) {
      fprintf(stderr, "Error: %s\n", strerror(errno));
      return -1;
    }
    int pid = wait(NULL);
    if (pid == -1) {
      fprintf(stderr, "Error: %s\n", strerror(errno));
      return -1;
    }
  }
}