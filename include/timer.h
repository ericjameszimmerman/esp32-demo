#ifndef timer_h
#define timer_h

#include "callbackHandler.h"
#include "monotonicTimestamp.h"
#include <stdint.h>

namespace platform {

class Timer
{
public:
  Timer();
  ~Timer();

  bool start(unsigned long newIntervalMilliseconds, bool autoRepeat);
  void stop();

  void update(MonotonicTimestamp timestamp);

  MonotonicTimestamp elapsedTimestamp;
  unsigned long intervalMilliseconds;
  bool repeat;
  bool started;
  CallbackHandler elapsed;
};

}   // namespace platform

#endif
