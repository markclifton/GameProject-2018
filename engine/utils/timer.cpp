#include "timer.h"

namespace utils
{
Timer::Timer()
{
    m_lastTick = std::chrono::high_resolution_clock::now();
}

double Timer::reset()
{
    std::chrono::duration<double> time = std::chrono::system_clock::now()-m_lastTick;
    m_lastTick = std::chrono::high_resolution_clock::now();
    return time.count();
}
}
