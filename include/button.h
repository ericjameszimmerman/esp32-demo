#ifndef button_H
#define button_H

#include "callbackHandler.h"
#include "monotonicTimestamp.h"

namespace bsp {

namespace buttonstates {
constexpr int off = 0;
constexpr int on = 1;
constexpr int pressed = 1;
}   // namespace buttonstates

class Button
{
public:
  Button(int digitalInputPin);
  ~Button();

  void sample();

  CallbackHandler buttonDown;
  CallbackHandler buttonRepeat;

  int buttonState() { return buttonState_; }

  unsigned long repeatMilliseconds;

private:
  void changeState(int newState);

  int digitalInputPin_;
  uint32_t inputSamples_;
  int buttonState_;
  MonotonicTimestamp repeatTimestamp_;
};

}   // namespace bsp

#if 0

// Variables will change:
int ledState = HIGH;        // the current state of the output pin
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
#endif

#endif
