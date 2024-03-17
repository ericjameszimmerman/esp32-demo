#include "oledDisplay.h"
#include "monotonicTimestamp.h"
#include <Wire.h>

namespace bsp {

#define SCREEN_WIDTH 128   // OLED display width, in pixels
#define SCREEN_HEIGHT 64   // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET -1         // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C   ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

OledDisplay::OledDisplay() : display_(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{
  demoSequencerStep_ = 0;
}

OledDisplay::~OledDisplay() {}

void OledDisplay::initialize()
{
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display_.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;   // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display_.display();
}

void OledDisplay::updateDemoSequencer()
{
  if (demoSequencerStep_ != 0)
  {
    MonotonicTimestamp now = MonotonicTimestamp::now();
    if (now > nextStateTimestamp_)
    {
      setDemoSequencerState(demoSequencerStep_ + 1);
    }
  }
}

void OledDisplay::setDemoSequencerState(int step)
{
  unsigned long delayMilliseconds = 1000;
  switch (step)
  {
  case 1:
    display_.clearDisplay();
    display_.setTextSize(2);   // Draw 2X-scale text
    display_.setTextColor(SSD1306_WHITE);
    display_.setCursor(10, 0);
    display_.println(F("Hello World!"));
    display_.display();   // Show initial text
    delayMilliseconds = 100;
    break;

  case 2:
    // Scroll in various directions, pausing in-between:
    display_.startscrollright(0x00, 0x0F);
    delayMilliseconds = 2000;
    break;

  case 3:
    display_.stopscroll();
    delayMilliseconds = 1000;
    break;

  case 4:
    display_.startscrollleft(0x00, 0x0F);
    delayMilliseconds = 2000;
    break;

  case 5:
    display_.stopscroll();
    delayMilliseconds = 1000;
    break;

  case 6:
    display_.startscrolldiagright(0x00, 0x07);
    delayMilliseconds = 2000;
    break;

  case 7:
    display_.startscrolldiagleft(0x00, 0x07);
    delayMilliseconds = 2000;
    break;

  case 8:
    display_.stopscroll();
    delayMilliseconds = 1000;
    break;

  case 9:
  default:
    step = 0;
    break;
  }

  nextStateTimestamp_ = MonotonicTimestamp::now();
  nextStateTimestamp_.addMilliseconds(delayMilliseconds);
  demoSequencerStep_ = step;
}

}   // namespace bsp