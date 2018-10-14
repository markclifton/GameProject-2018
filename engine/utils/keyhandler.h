#pragma once

namespace utils
{
    class KeyHandler
    {
    public:
        virtual void process(int key, int scancode, int action, int mods) = 0;
    };
}
