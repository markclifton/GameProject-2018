#include "keyhandler.h"

#include <GLFW/glfw3.h>

#include <iostream>


namespace utils
{
    KeyHandler::KeyHandler(Camera* camera)
        : m_camera(camera)
    {
    }

    void KeyHandler::process(int key, int /*scancode*/, int action, int /*mods*/)
    {
        //std::cout << "Key Pressed: " << key << std::endl;
        if(key == GLFW_KEY_W  )//&& action == GLFW_PRESS)
        {
            //m_camera->Move(Direction::FORWARD);
        }
        else if(key == GLFW_KEY_S  )//&& action == GLFW_PRESS)
        {
            //m_camera->Move(Direction::BACK);
        }
        else if(key == GLFW_KEY_A  )//&& action == GLFW_PRESS)
        {
            //m_camera->Move(Direction::LEFT);
        }
        else if(key == GLFW_KEY_D  )//&& action == GLFW_PRESS)
        {
            //m_camera->Move(Direction::RIGHT);
        }
        else if(key == GLFW_KEY_Q  )//&& action == GLFW_PRESS)
        {
            //m_camera->ChangeHeading(.01f);
        }
        else if(key == GLFW_KEY_E  )//&& action == GLFW_PRESS)
        {
            //m_camera->ChangeHeading(-.01f);
        }
    }
}

