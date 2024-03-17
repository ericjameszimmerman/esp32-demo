#include "led.h"
#include <Arduino.h>

namespace bsp {

Led::Led(int digitalOutputPin) : digitalOutputPin_(digitalOutputPin) {}

Led::~Led() {}

void Led::initialize()
{
  pinMode(digitalOutputPin_, OUTPUT);
}

void Led::setOutput(bool on)
{
  on_ = on;
  digitalWrite(digitalOutputPin_, on ? HIGH : LOW);
}

void Led::toggle()
{
  setOutput(!on_);
}

}   // namespace bsp
