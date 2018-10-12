#pragma once

#include "managers/contextmanager.h"
#include "managers/windowmanager.h"

class Game
{
public:
    Game();
    virtual ~Game() = default;

    void run();

protected:
    virtual void setup();

private:
    ContextManager m_contextManager;
    WindowManager m_windowManager;
};
