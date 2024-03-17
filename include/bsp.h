#ifndef bsp_h
#define bsp_h

#include "button.h"
#include "fixedLinkedList.h"
#include "led.h"
#include "oledDisplay.h"

namespace bsp {

class BspClass
{
public:
  BspClass();
  ~BspClass();

  void initialize();
  void updatePeriodic();

  Button upButton;
  Button downButton;
  Button leftButton;
  Button rightButton;
  Button centerButton;

  Led activityLed;

  OledDisplay display;

private:
  FixedLinkedList<Button*, 5> buttonList_;
  MonotonicTimestamp sampleTimestamp_;
};

}   // namespace bsp

extern bsp::BspClass Bsp;

#endif
