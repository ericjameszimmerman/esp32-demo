#ifndef platform_h
#define platform_h

#include "callbackFifo.h"
#include "platformConstants.h"
#include "timerSubsystem.h"
#include <stdint.h>

// Define the callback type for ease of use
using PlatformCallbackType = std::function<void(int, size_t)>;

namespace platform {

class PlatformClass
{
public:
  PlatformClass();
  ~PlatformClass();

  void runPeriodic();

  TimerSubsystem timers;

  bool enqueueCallback(const CallbackHandler& callback, int intValue, size_t sizeValue);

private:
  void initialize();
  CallbackFIFO<CallbackHandler, 100> callbackFifo_;

  unsigned long lastTimestamp_;
};

}   // namespace platform

extern platform::PlatformClass Platform;

#endif
