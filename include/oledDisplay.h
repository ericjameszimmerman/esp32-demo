#ifndef oledDisplay_H
#define oledDisplay_H

#include "monotonicTimestamp.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


namespace bsp {

class OledDisplay
{
public:
  OledDisplay();
  ~OledDisplay();

  void initialize();
  void updateDemoSequencer();
  void setDemoSequencerState(int step);

private:
  Adafruit_SSD1306 display_;
  int demoSequencerStep_;
  MonotonicTimestamp nextStateTimestamp_;
};

}   // namespace bsp

#endif