#include "platform.h"
#include <Arduino.h>

namespace platform {

PlatformClass::PlatformClass()
{
  lastTimestamp_ = 0;
}

PlatformClass::~PlatformClass() {}

bool PlatformClass::enqueueCallback(const CallbackHandler& callback, int intValue, size_t sizeValue)
{
  return callbackFifo_.enqueue(callback, intValue, sizeValue);
}

void PlatformClass::runPeriodic()
{
  // update soft timers
  unsigned long now = millis();
  if (now != lastTimestamp_)
  {
    timers.updatePeriodic();
    lastTimestamp_ = now;
  }

  // Dequeue and execute callbacks
  while (callbackFifo_.size() > 0)
  {
    callbackFifo_.dequeueAndExecute();
  }
}

}   // namespace platform
