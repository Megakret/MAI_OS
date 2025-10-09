namespace OSWrapper {
using ThreadFunc = typeof(void *(void *)) *;
class Thread {
public:
  Thread(ThreadFunc);
  Thread(const Thread &); // for the vector :(
  Thread(const Thread &&) noexcept;
  Thread &operator=(const Thread &) = delete;
  Thread &operator=(Thread &&) noexcept;
  virtual ~Thread() noexcept;

  virtual void Join();
  virtual void Detach();
  virtual void Run(void *);

private:
  ThreadFunc func_;
  struct OSSpecificData;
  OSSpecificData *data_;
};
} // namespace OSWrapper
