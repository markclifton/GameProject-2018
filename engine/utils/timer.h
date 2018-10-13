#pragma once

#include <chrono>

namespace utils
{
    class Timer
    {
    public:
        Timer();
        double reset();

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTick;
    };
}
