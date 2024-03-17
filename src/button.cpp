#include "button.h"
#include "platform.h"
#include <Arduino.h>

constexpr uint32_t BUTTON_SAMPLE_MASK = 0x7ff;

namespace bsp {

Button::Button(int digitalInputPin) : digitalInputPin_(digitalInputPin)
{
  inputSamples_ = 0;
  repeatMilliseconds = 0;
}

Button::~Button() {}

void Button::sample()
{
  // read the state of the switch into a local variable:
  int reading = digitalRead(digitalInputPin_);

  inputSamples_ = ((inputSamples_ << 1) | (reading == HIGH) ? 0 : 1) & BUTTON_SAMPLE_MASK;

  if (buttonState_ == buttonstates::off)
  {
    if (inputSamples_ == BUTTON_SAMPLE_MASK)
    {
      // transition to pressed
      changeState(buttonstates::pressed);
    }
  }
  else
  {
    if (inputSamples_ == 0)
    {
      // transition to unpressed
      changeState(buttonstates::off);
    }
    else
    {
      // check for repeat press events
      if (repeatMilliseconds && buttonRepeat.isSet())
      {
        MonotonicTimestamp now = MonotonicTimestamp::now();
        if (now > repeatTimestamp_)
        {
          repeatTimestamp_ = now;
          repeatTimestamp_.addMilliseconds(repeatMilliseconds);
          Platform.enqueueCallback(buttonRepeat, platform::eventtypes::button, platform::buttonevents::repeat);
        }
      }
    }
  }
}

void Button::changeState(int newState)
{
  if (buttonState_ != newState)
  {
    buttonState_ = newState;

    if (newState == buttonstates::pressed)
    {
      if (buttonDown.isSet())
      {
        if (repeatMilliseconds)
        {
          repeatTimestamp_ = MonotonicTimestamp::now();
          repeatTimestamp_.addMilliseconds(repeatMilliseconds);
        }

        Platform.enqueueCallback(buttonDown, platform::eventtypes::button, platform::buttonevents::pressed);
      }
    }
    else if (newState == buttonstates::off)
    {
      // todo: add released callback?
    }
    else
    {
      buttonState_ = buttonstates::off;
    }
  }
}

}   // namespace bsp
