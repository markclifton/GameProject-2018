#pragma once

#include "camera/camera.h"
#include "managers/contextmanager.h"
#include "managers/shadermanager.h"
#include "managers/windowmanager.h"

class Game
{
public:
    Game();
    virtual ~Game();

    void run();

protected:
    virtual void setup();

private:
    managers::ContextManager m_contextManager;
    managers::ShaderManager m_shaderManager;
    std::unique_ptr<managers::WindowManager> m_windowManager;
    std::unique_ptr<Camera3D> m_camera;
};
