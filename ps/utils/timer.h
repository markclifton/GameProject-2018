#pragma once

#include <chrono>

namespace ps
{
namespace utils
{
class Timer
{
public:
    Timer();
    double reset();
    double get();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTick;
};
}
}
