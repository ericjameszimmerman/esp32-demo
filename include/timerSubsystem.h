#ifndef timerSubsystem_H
#define timerSubsystem_H

#include "fixedLinkedList.h"
#include "timer.h"

namespace platform {

class TimerSubsystem
{
public:
  TimerSubsystem();
  ~TimerSubsystem();

  void updatePeriodic();
  void add(Timer* timer);

private:
  FixedLinkedList<Timer*, 3> timerList_;
};

}   // namespace platform

#endif
