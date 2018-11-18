#pragma once

#include "managers/contextmanager.h"
#include "managers/soundmanager.h"
#include "managers/shadermanager.h"
#include "managers/texturemanager.h"
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
    managers::SoundManager m_soundManager;
    managers::ShaderManager m_shaderManager;
    managers::TextureManager m_textureManager;
    managers::WindowManager m_windowManager;
};
