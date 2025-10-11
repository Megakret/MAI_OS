#include <pthread.h>
#include <system_error>

#include <thread.hpp>

namespace OSWrapper {
struct Thread::OSSpecificData {
  pthread_t pthread;
};
Thread::Thread(ThreadFunc func) : func_(func), data_(new OSSpecificData()) {}
void Thread::Run(void *thread_arg) {
  int err = pthread_create(&(data_->pthread), NULL, func_, thread_arg);
  if (err != 0) {
    throw std::system_error(std::error_code(err, std::system_category()));
  }
}
void Thread::Join() {
  int err = pthread_join(data_->pthread, NULL);
  if (err != 0) {
    throw std::system_error(std::error_code(err, std::system_category()));
  }
}
void Thread::Detach() {
  int err = pthread_detach(data_->pthread);
  if (err != 0) {
    throw std::system_error(std::error_code(err, std::system_category()));
  }
}
Thread::~Thread() {};
Thread::Thread(const Thread &other)
    : func_(other.func_), data_(new OSSpecificData()) {}
} // namespace OSWrapper
