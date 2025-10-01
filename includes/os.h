#include <stdlib.h>
#include <unistd.h>
typedef int pipe_t;
typedef int pid_t;
typedef int file_t;
int CreatePipe(pipe_t fd_buffer[2]);
pid_t CloneProcess();
int Exec(const char *executable_path);
void PrintLastError();
int WaitForChild();
void ClosePipe(pipe_t pipe_part);
int WritePipe(pipe_t pipe, void *buffer, size_t bytes);
int ReadPipe(pipe_t pipe, void *buffer, size_t bytes);
int LinkStdinWithPipe(pipe_t output_pipe);
int LinkStderrWithPipe(pipe_t output_pipe);
//returns -1 on failure, 0 for still running and 1 for exited
int HasTerminated(pid_t child_process);
