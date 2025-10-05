#include <os.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
const int ChildDeathSig = SIGCHLD;
const int BrokenPipeSig = SIGPIPE;
int CreatePipe(pipe_t fd_buffer[2]) { return pipe(fd_buffer); }
pid_t CloneProcess() { return fork(); }
int Exec(const char *executable_path) {
  return execl(executable_path, executable_path, NULL);
}
void PrintLastError() { fprintf(stderr, "Error: %s\n", strerror(errno)); }
int WaitForChild() { return wait(NULL); }
int ClosePipe(pipe_t pipe_part) { return close(pipe_part); }
int WritePipe(pipe_t pipe, void *buffer, size_t bytes) {
  return write(pipe, buffer, bytes);
}
int ReadPipe(pipe_t pipe, void *buffer, size_t bytes) {
  return read(pipe, buffer, bytes);
}
int LinkStdinWithPipe(pipe_t output_pipe) {
  return dup2(output_pipe, STDIN_FILENO);
}
int LinkStderrWithPipe(pipe_t output_pipe) {
  return dup2(output_pipe, STDERR_FILENO);
}
void AddSignalHandler(signal_t signal_type, SignalHandler_t signal_handler) {
  signal(signal_type, signal_handler);
}
int ReadFromStdin(char *buffer, size_t buffer_size) {
  return read(STDIN_FILENO, buffer, buffer_size);
}
