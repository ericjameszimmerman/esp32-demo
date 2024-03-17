#include "app.h"
#include "bsp.h"
#include "platform.h"

App::App() {}

App::~App() {}

void App::start()
{
  Platform.timers.add(&backgroundTimer_);
  backgroundTimer_.elapsed.setCallback(
    std::bind(&App::onBackgroundTimerElapsed, this, std::placeholders::_1, std::placeholders::_2));
  backgroundTimer_.start(1000, true);
  Bsp.display.setDemoSequencerState(1);
}

void App::onBackgroundTimerElapsed(int arg1, size_t arg2)
{
  Bsp.activityLed.toggle();
}
