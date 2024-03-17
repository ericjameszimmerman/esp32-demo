#include "bsp.h"
#include <Arduino.h>

namespace bsp {

BspClass::BspClass()
    : upButton(36), downButton(39), leftButton(34), rightButton(32), centerButton(33), activityLed(LED_BUILTIN)
{
  buttonList_.add(&upButton);
  buttonList_.add(&downButton);
  buttonList_.add(&leftButton);
  buttonList_.add(&rightButton);
  buttonList_.add(&centerButton);
}

BspClass::~BspClass() {}

void BspClass::initialize()
{
  Serial.begin(115200);

  Serial.println("BspClass::initialize()");

  activityLed.initialize();
  display.initialize();
}

void BspClass::updatePeriodic()
{
  MonotonicTimestamp now = MonotonicTimestamp::now();
  if (now > sampleTimestamp_)
  {
    sampleTimestamp_ = now;
    sampleTimestamp_.addMilliseconds(14);

    for (auto it = buttonList_.begin(); it != buttonList_.end(); ++it)
    {
      Button* button = *it;
      if (button)
      {
        button->sample();
      }
    }

    display.updateDemoSequencer();
  }
}

}   // namespace bsp
