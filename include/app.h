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
  void onDownButtonPressed(int arg1, size_t arg2);
  void onUpButtonPressed(int arg1, size_t arg2);
  void onLeftButtonPressed(int arg1, size_t arg2);
  void onRightButtonPressed(int arg1, size_t arg2);
  void onCenterButtonPressed(int arg1, size_t arg2);

  platform::Timer backgroundTimer_;
  MonotonicTimestamp displaySequencerTs_;
};

#endif