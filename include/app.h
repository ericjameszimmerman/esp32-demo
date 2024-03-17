#ifndef app_H
#define app_H

#include "monotonicTimestamp.h"
#include "timer.h"

class App
{
public:
  App();
  ~App();

  void start();

private:
  void onBackgroundTimerElapsed(int arg1, size_t arg2);

  platform::Timer backgroundTimer_;
  MonotonicTimestamp displaySequencerTs_;
};

#endif