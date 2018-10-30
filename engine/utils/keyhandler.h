#pragma once

namespace utils
{
class KeyHandler
{
public:
    virtual ~KeyHandler() = default;
    virtual void process(int key, int scancode, int action, int mods) = 0;
};
}
