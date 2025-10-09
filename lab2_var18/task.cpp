#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <thread.hpp>
bool has_found_any_occurence = false;
const int kBuffer = 1000;
typedef struct {
  const std::string &field;
  const std::string &sample;
  std::size_t start_pos;
  std::size_t end_pos;
} ThreadArg;
void *StartThread(void *void_arg) {
  ThreadArg *args = static_cast<ThreadArg *>(void_arg);
  for (int i = args->start_pos; i < args->end_pos; ++i) {
    bool has_found = true;
    for (int j = i; j < args->field.length() && j - i < args->sample.length();
         ++j) {
      if (args->field[j] != args->sample[j - i]) {
        has_found = false;
        break;
      }
    }
    if (has_found) {
      has_found_any_occurence = true;
      std::cout << "Found sample at index: " << i << '\n';
    }
  }
  return NULL;
}
int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "You must enter the number of threads for the programm as an "
                 "argument\n";
    return -1;
  }

  int arg1;
  try {
    arg1 = std::stoi(std::string(argv[1]));
  } catch (const std::invalid_argument &) {
    std::cout << "You provided weird string as a number\n";
    return -1;
  } catch (const std::out_of_range &) {
    std::cout << "You provided too large number\n";
  }
  const int kThreadCount = arg1;

  std::cout << "Enter the string: ";
  std::string field;
  std::getline(std::cin, field);
  std::cout << "Enter the substring to find: ";
  std::string sample;
  std::getline(std::cin, sample);
  std::vector<ThreadArg> args(kThreadCount, {field, sample});
  for (int i = 0; i < kThreadCount; ++i) {
    args[i].start_pos = field.length() / kThreadCount * i;
    args[i].end_pos = field.length() / kThreadCount * (i + 1);
  }
  std::vector<OSWrapper::Thread> threads(kThreadCount, &StartThread);
  for (int i = 0; i < kThreadCount; ++i) {
    threads[i].Run(&args[i]);
  }
  for (int i = 0; i < kThreadCount; ++i) {
    threads[i].Join();
  }
  if (!has_found_any_occurence) {
    std::cout << "No such substrings were found\n";
  }
}
