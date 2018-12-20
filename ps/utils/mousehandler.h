#pragma once

namespace ps
{
namespace utils
{
class MouseHandler
{
public:
    virtual ~MouseHandler() = default;

    virtual void process(double xpos, double ypos) = 0;
    virtual void process(int button, int action, int mods) = 0;
private:
};
}
}
