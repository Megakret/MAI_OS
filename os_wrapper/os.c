#include "os.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
int CreatePipe(pipe_t fd_buffer[2]) { return pipe(fd_buffer); }
pid_t CloneProcess() { return fork(); }
int Exec(const char *executable_path) {
  return execl(executable_path, executable_path, NULL);
}
void PrintLastError() { fprintf(stderr, "Error: %s\n", strerror(errno)); }
int WaitForChild() { return wait(NULL); }
void ClosePipe(pipe_t pipe_part) { close(pipe_part); }
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
int HasTerminated(pid_t child_process){
	int status;
	return waitpid(child_process, &status, WNOHANG);
}
