#include "app.h"
#include "bsp.h"
#include "platform.h"
#include <Arduino.h>
#include <SPI.h>


using namespace platform;

PlatformClass Platform;
bsp::BspClass Bsp;
App app;

void setup()
{
  Bsp.initialize();
  app.start();
}

void loop()
{
  Bsp.updatePeriodic();
  Platform.runPeriodic();
}
