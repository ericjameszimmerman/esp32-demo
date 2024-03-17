#ifndef platformConstants_H
#define platformConstants_H

#include <stddef.h>
#include <stdint.h>

namespace platform {
namespace eventtypes {
constexpr int timer = 1;
constexpr int button = 2;
}   // namespace eventtypes

namespace timerevents {
constexpr size_t elapsed = 1;
}

namespace buttonevents {
constexpr size_t pressed = 1;
constexpr size_t repeat = 2;
}   // namespace buttonevents
}   // namespace platform

#endif
