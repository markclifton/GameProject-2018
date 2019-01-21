#include "timer.h"

namespace ps
{
namespace utils
{
Timer::Timer()
{
    m_lastTick = std::chrono::steady_clock::now();
}

double Timer::reset()
{
    auto time = get();
    m_lastTick = std::chrono::steady_clock::now();
    return time;
}

double Timer::get()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - m_lastTick).count() * 0.000001;
}

}
}
