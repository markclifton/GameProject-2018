#include "game.h"

#include <iostream>

#include "shaders/shader.h"
#include "utils/timer.h"

Game::Game()
    : m_contextManager()
    , m_windowManager()
{
}

void Game::run()
{
    m_windowManager.toggleVsync(false);

    setup();
    Shader s;

    Timer t;
    int ticks = 0;
    while( !m_windowManager.shouldClose() )
    {
        if( ticks++ > 100)
        {
            std::cerr << 1.0/(t.reset()/ticks) << "\n";
            ticks = 0;
        }

        m_contextManager.runContext();
        m_windowManager.refresh();
    }
}

void Game::setup()
{
    int id;
    if( !m_contextManager.addContext(id, new Context()) )
        std::cerr << "Failed to add context\n";
    if( !m_contextManager.setContext(id) )
        std::cerr << "Failed to set context\n";
}
