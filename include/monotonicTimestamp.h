#ifndef MONOTONIC_TIMESTAMP_H
#define MONOTONIC_TIMESTAMP_H

#include "timeSpan.h"
#include <Arduino.h>
#include <stdint.h>


class MonotonicTimestamp
{
public:
  MonotonicTimestamp() : timestamp_(0) {}
  explicit MonotonicTimestamp(unsigned long initialTimestamp) : timestamp_(initialTimestamp) {}

  static MonotonicTimestamp now()
  {
    MonotonicTimestamp time;

    time = millis();

    return time;
  }

  // Overload the assignment operator for MonotonicTimestamp objects
  MonotonicTimestamp& operator=(const MonotonicTimestamp& other)
  {
    // Check for self-assignment
    if (this != &other)
    {
      setTimestamp(other.timestamp_);
    }
    return *this;
  }

  // Allow assignment from unsigned long directly
  MonotonicTimestamp& operator=(unsigned long newTimestamp)
  {
    setTimestamp(newTimestamp);
    return *this;
  }

  TimeSpan operator-(const MonotonicTimestamp& rhs)
  {
    TimeSpan timeSpan(timestamp_, rhs.timestamp());
    return timeSpan;
  }

  // Set the timestamp, ensuring it does not move backwards
  void setTimestamp(unsigned long newTimestamp) { timestamp_ = newTimestamp; }

  // Increment the timestamp by a specified amount.
  void addMilliseconds(unsigned long amount) { timestamp_ += amount; }

  void addSeconds(int seconds) { timestamp_ += (seconds * 1e3); }

  // Comparison operators
  bool operator==(const MonotonicTimestamp& other) const { return timestamp_ == other.timestamp_; }

  bool operator!=(const MonotonicTimestamp& other) const { return timestamp_ != other.timestamp_; }

  bool operator<(const MonotonicTimestamp& other) const { return timestamp_ < other.timestamp_; }

  bool operator<=(const MonotonicTimestamp& other) const { return timestamp_ <= other.timestamp_; }

  bool operator>(const MonotonicTimestamp& other) const { return timestamp_ > other.timestamp_; }

  bool operator>=(const MonotonicTimestamp& other) const { return timestamp_ >= other.timestamp_; }

  // Get the current timestamp value
  unsigned long timestamp() const { return timestamp_; }

private:
  unsigned long timestamp_;
};

#endif   // MONOTONIC_TIMESTAMP_HPP
