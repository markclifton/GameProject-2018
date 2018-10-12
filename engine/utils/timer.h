#pragma once

#include <chrono>

class Timer
{
public:
    Timer();
    double reset();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTick;
};
