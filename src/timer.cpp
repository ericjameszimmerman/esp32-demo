#include "timer.h"
#include "platform.h"
#include <Arduino.h>

namespace platform {

Timer::Timer()
{
  started = false;
  repeat = false;
}

Timer::~Timer() {}

void Timer::update(MonotonicTimestamp timestamp)
{
  if (started)
  {
    if (timestamp > elapsedTimestamp)
    {
      Platform.enqueueCallback(elapsed, eventtypes::timer, timerevents::elapsed);
      if (repeat)
      {
        elapsedTimestamp = MonotonicTimestamp::now();
        elapsedTimestamp.addMilliseconds(intervalMilliseconds);
      }
      else
      {
        started = false;
      }
    }
  }
}

bool Timer::start(unsigned long newIntervalMilliseconds, bool autoRepeat)
{
  if (started)
  {
    stop();
  }

  elapsedTimestamp = MonotonicTimestamp::now();
  intervalMilliseconds = newIntervalMilliseconds;
  elapsedTimestamp.addMilliseconds(newIntervalMilliseconds);
  repeat = autoRepeat;
  started = true;
  return true;
}

void Timer::stop()
{
  started = false;
}

}   // namespace platform
