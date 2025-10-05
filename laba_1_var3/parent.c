#include <stdbool.h>
#include <stdio.h>

#include <os.h>
const size_t kBuffer = 100;
bool PrintErrorFromChild(pipe_t pipe) {
  char buffer[kBuffer];
  int bytesN = ReadPipe(pipe, buffer, kBuffer);
  bool has_error = false;
  if (bytesN > 0) {
    has_error = true;
    fprintf(stderr, "Error from child: ");
  }
  while (bytesN > 0) {
    fwrite(buffer, sizeof(char), bytesN, stderr);
    bytesN = ReadPipe(pipe, buffer, kBuffer);
  }
  return has_error;
}
pipe_t err_pipe_in;
void OnChildKilled(signal_t signum) {
  bool has_error = PrintErrorFromChild(err_pipe_in);
  if (has_error) {
    exit(-1);
  }
}
int main() {
  AddSignalHandler(ChildDeathSig, &OnChildKilled);
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
  pipe_t err_pipe[2];
  err = CreatePipe(input_pipe);
  if (err == -1) {
    PrintLastError();
    return -1;
  }
  err = CreatePipe(err_pipe);
  if (err == -1) {
    PrintLastError();
    return -1;
  }
  err_pipe_in = err_pipe[0];
  pid_t child_id = CloneProcess();
  if (child_id == 0) {
    // child
    // replacing stdin
    err = LinkStdinWithPipe(input_pipe[0]);
    if (err == -1) {
      PrintLastError();
      return -1;
    }
    err = LinkStderrWithPipe(err_pipe[1]);
    if (err == -1) {
      PrintLastError();
      return -1;
    }
    ClosePipe(input_pipe[1]);
    ClosePipe(err_pipe[0]);
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
    ClosePipe(input_pipe[0]);
    ClosePipe(err_pipe[1]);
    char buffer[kBuffer];
    int read_chars = 0;
    while ((read_chars = ReadFromStdin(buffer, kBuffer)) > 0) {
      err = WritePipe(input_pipe[1], buffer, read_chars);
      if (err == -1) {
        PrintLastError();
        return -1;
      }
    }
    ClosePipe(input_pipe[1]);
    if (err == -1) {
      PrintLastError();
      return -1;
    }
    PrintErrorFromChild(err_pipe[0]);
    if (err == -1) {
      PrintLastError();
      return -1;
    }
    err = WaitForChild();
    if (err == -1) {
      PrintLastError();
      return -1;
    }
  }
}
