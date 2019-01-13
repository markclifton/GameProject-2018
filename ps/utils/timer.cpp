#include "timer.h"

namespace ps
{
namespace utils
{
Timer::Timer()
{
    m_lastTick = std::chrono::high_resolution_clock::now();
}

double Timer::reset()
{
    auto time = get();
    m_lastTick = std::chrono::high_resolution_clock::now();
    return time;
}

double Timer::get()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_lastTick).count();
}

}
}
