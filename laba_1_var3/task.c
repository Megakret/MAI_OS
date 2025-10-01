#include <stdio.h>
#include <os.h>
const char *kOutputFileName = "output.txt";
int main() {
  int num = 0;
  int err = scanf("%d", &num);
  if (err == -1) {
    PrintLastError();
    return -1;
  }
  int divider = 1;
	int scanned = 0;
  while ((scanned = scanf("%d", &divider)) > 0) {
    if (divider == 0) {
			fprintf(stderr, "Error: division by 0 occured. Killing child process\n");
      return -1;
    }
    num /= divider;
  }
		if(scanned == 0){
			fprintf(stderr, "Error: Wrong format occured, stopped reading. Maybe you wrote letters\n");	
		}
  // Error occured on reading numbers(not EOF)
  if (ferror(stdin)) {
    PrintLastError();
    return -1;
  }
  FILE *output_file = fopen(kOutputFileName, "w");
  // Error occured while opening a file
  if (output_file == NULL) {
    PrintLastError();
    return -1;
  }

  int written = fprintf(output_file, "%d\n", num);
  // Number wasn't written properly
  if (written <= 0) {
    PrintLastError();
    fclose(output_file);
    return -1;
  }
  err = fclose(output_file);
  if (err != 0) {
    PrintLastError();
    return -1;
  }
  return 0;
}
