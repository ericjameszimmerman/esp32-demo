#ifndef callback_H
#define callback_H

#include <functional>

class CallbackHandler
{
public:
  // Define a callback type that takes an int and returns void
  using CallbackType = std::function<void(int, size_t)>;

  // Method to set the callback
  void setCallback(CallbackType callback) { this->callback = callback; }

  // Method to invoke the callback
  void invokeCallback(int arg1, size_t arg2)
  {
    if (callback)
    {   // Check if callback is set
      callback(arg1, arg2);
    }
  }

  bool isSet() { return (callback) ? true : false; }

private:
  CallbackType callback;   // The callback
};

#endif
