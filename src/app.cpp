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
  Bsp.downButton.buttonDown.setCallback(
    std::bind(&App::onDownButtonPressed, this, std::placeholders::_1, std::placeholders::_2));
  Bsp.upButton.buttonDown.setCallback(
    std::bind(&App::onUpButtonPressed, this, std::placeholders::_1, std::placeholders::_2));
  Bsp.leftButton.buttonDown.setCallback(
    std::bind(&App::onLeftButtonPressed, this, std::placeholders::_1, std::placeholders::_2));
  Bsp.rightButton.buttonDown.setCallback(
    std::bind(&App::onRightButtonPressed, this, std::placeholders::_1, std::placeholders::_2));
  Bsp.centerButton.buttonDown.setCallback(
    std::bind(&App::onCenterButtonPressed, this, std::placeholders::_1, std::placeholders::_2));
}

void App::onBackgroundTimerElapsed(int arg1, size_t arg2)
{
  Bsp.activityLed.toggle();
}

void App::onDownButtonPressed(int arg1, size_t arg2)
{
  Serial.println("Down Pressed");
}

void App::onUpButtonPressed(int arg1, size_t arg2)
{
  Serial.println("Up Pressed");
}

void App::onLeftButtonPressed(int arg1, size_t arg2)
{
  Serial.println("Left Pressed");
}

void App::onRightButtonPressed(int arg1, size_t arg2)
{
  Serial.println("Right Pressed");
}

void App::onCenterButtonPressed(int arg1, size_t arg2)
{
  Serial.println("Center Pressed");
}
