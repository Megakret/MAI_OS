#include "os.h"
#include <stdio.h>
const size_t kBuffer= 100;
int main() {
  int err = printf("Write a filepath for a child process executable: ");
  if (err < 0) {
    PrintLastError();
    return -1;
  }
  char child_name[kBuffer];
  char *s = fgets(child_name, kBuffer, stdin);
  if (s == NULL) {
    PrintLastError();
    return -1;
  }
  // Removing \n from filepath
  for (int i = 0; i < kBuffer; i++) {
    if (s[i] == '\n') {
      s[i] = '\0';
      break;
    }
  }
  pipe_t input_pipe[2];
  err = CreatePipe(input_pipe);
  if (err == -1) {
    PrintLastError();
    return -1;
  }
  pid_t child_id = CloneProcess();
  if (child_id == 0) {
    // child
    // replacing stdin
    err = LinkStdinWithPipe(input_pipe[0]);
    if (err == -1) {
      PrintLastError();
      return -1;
    }
    ClosePipe(input_pipe[1]);
    if (err == -1) {
      PrintLastError();
      return -1;
    }
    err = Exec(child_name);
    if (err == -1) {
      PrintLastError();
      return -1;
    }
    return -1;
  } else if (child_id == -1) {
    // error
		PrintLastError();
    return -1;
  } else {
    // parent
    char c;
    while ((c = getchar()) != EOF) {
      err = WritePipe(input_pipe[1], &c, sizeof(char));
      if (err == -1) {
        PrintLastError();
        return -1;
      }
    }
    ClosePipe(input_pipe[0]);
    ClosePipe(input_pipe[1]);
    if (err == -1) {
      PrintLastError();
      return -1;
    }
    int err = WaitForChild();
    if (err == -1) {
      PrintLastError();
      return -1;
    }
  }
}
