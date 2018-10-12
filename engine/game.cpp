#include "game.h"

#include <iostream>

#include "shaders/shader.h"

Game::Game()
    : m_contextManager()
    , m_windowManager()
{
}

void Game::run()
{
    setup();
    Shader s;

    while( !m_windowManager.shouldClose() )
    {
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
