#ifndef led_H
#define led_H

namespace bsp {

class Led
{
public:
  Led(int digitalOutputPin);
  ~Led();

  void initialize();
  void setOutput(bool on);
  void toggle();

private:
  int digitalOutputPin_;
  bool on_;
};

}   // namespace bsp

#endif
