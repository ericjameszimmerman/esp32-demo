#ifndef TIME_SPAN_HPP
#define TIME_SPAN_HPP

#include <stdint.h>
typedef uint32_t milliseconds_t;
typedef int32_t seconds_t;

class TimeSpan
{
public:
  // Default constructor initializes to a zero-length time span
  TimeSpan() : delta_(0) {}

  TimeSpan(unsigned long lhs, unsigned long rhs) { delta_ = (lhs < rhs) ? -((long)(rhs - lhs)) : (long)(lhs - rhs); }

  // Set the time span based on two MonotonicTimestamps
  void setSpan(long deltaArg) { delta_ = deltaArg; }

  // Get the delta in unsigned long format
  long delta() const { return delta_; }

  // Other useful methods could include:
  // Adding or subtracting time from the TimeSpan
  // Comparing two TimeSpans
  // Conversion to different time units (seconds, minutes, etc.), assuming a base unit for the timestamp

private:
  long delta_;   // The delta between two timestamps
};

#endif   // TIME_SPAN_HPP
