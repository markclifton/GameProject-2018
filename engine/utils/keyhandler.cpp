#include "keyhandler.h"

#include <iostream>

namespace utils
{
    KeyHandler::KeyHandler()
    {
    }

    void KeyHandler::process(int key, int, int, int) //int scancode, int action, int mods)
    {
        std::cout << "Key Pressed: " << key << std::endl;
    }
}

