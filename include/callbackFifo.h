#ifndef callbackFifo_H
#define callbackFifo_H

#include <functional>

template <typename CallbackType, size_t MaxSize> class CallbackFIFO
{
public:
  struct Item
  {
    CallbackType callback;
    int intValue;
    size_t sizeValue;
  };

private:
  Item buffer[MaxSize];   // C-style array
  size_t head = 0;
  size_t tail = 0;
  size_t count = 0;

public:
  bool enqueue(const CallbackType& callback, int intValue, size_t sizeValue)
  {
    if (count >= MaxSize)
    {
      // FIFO is full, cannot enqueue
      return false;
    }

    buffer[tail].callback = callback;
    buffer[tail].intValue = intValue;
    buffer[tail].sizeValue = sizeValue;

    tail = (tail + 1) % MaxSize;
    ++count;

    return true;
  }

  bool dequeueAndExecute()
  {
    if (count == 0)
    {
      // FIFO is empty, cannot dequeue
      return false;
    }

    // Execute the callback
    buffer[head].callback.invokeCallback(buffer[head].intValue, buffer[head].sizeValue);

    head = (head + 1) % MaxSize;
    --count;

    return true;
  }

  size_t size() const { return count; }
};

#endif