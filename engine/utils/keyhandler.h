#pragma once

#include "../camera/camera.h"

namespace utils
{
    class KeyHandler
    {
    public:
        KeyHandler(Camera* camera);
        virtual ~KeyHandler() = default;

        virtual void process(int key, int scancode, int action, int mods);
    private:
        Camera* m_camera;
    };
}
