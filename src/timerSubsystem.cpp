#include "timerSubsystem.h"

namespace platform {

TimerSubsystem::TimerSubsystem() {}

TimerSubsystem::~TimerSubsystem() {}

void TimerSubsystem::updatePeriodic()
{
  MonotonicTimestamp now = MonotonicTimestamp::now();

  for (auto it = timerList_.begin(); it != timerList_.end(); ++it)
  {
    Timer* timer = *it;
    if (timer)
    {
      timer->update(now);
    }
  }
}

void TimerSubsystem::add(Timer* timer)
{
  timerList_.add(timer);
}

}   // namespace platform