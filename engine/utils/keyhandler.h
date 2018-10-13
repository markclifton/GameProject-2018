#pragma once

namespace utils
{
    class KeyHandler
    {
    public:
        KeyHandler();
        virtual ~KeyHandler() = default;

        virtual void process(int key, int scancode, int action, int mods);
    private:

    };
}
