#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
const char *OUTPUT_FILE = "output.txt";
int main() {
  int num = 0;
  int err = scanf("%d", &num);
  if (err == -1) {
    fprintf(stderr, "Error: %s\n", strerror(errno));
    return -1;
  }
  int divider = 1;
  while (scanf("%d", &divider) > 0) {
    if (divider == 0) {
      fprintf(stderr, "Division by 0 error");
      return -1;
    }
    num /= divider;
  }
  // Error occured on reading numbers(not EOF)
  if (ferror(stdin)) {
    fprintf(stderr, "Error: %s\n", strerror(errno));
    return -1;
  }
  FILE *output = fopen(OUTPUT_FILE, "w");
  // Error occured while opening a file
  if (output == NULL) {
    fprintf(stderr, "Error: %s\n", strerror(errno));
    return -1;
  }
  int written = fprintf(output, "%d\n", num);
  // Number wasn't written properly
  if (written <= 0) {
    fprintf(stderr, "Error: %s\n", strerror(errno));
    fclose(output);
    return -1;
  }
  err = fclose(output);
  if (err != 0) {
    fprintf(stderr, "Error: %s\n", strerror(errno));
    return -1;
  }
  return 0;
}