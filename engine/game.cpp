#include "game.h"

#include <iostream>

#include "managers/windowmanager.h"
#include "shaders/shader.h"

Game::Game()
    : m_contextManager()
{
    WindowManager::instance();
}

void Game::run()
{
    setup();
    Shader s;

    while( !WindowManager::instance().shouldClose() )
    {
        m_contextManager.runContext();
        WindowManager::instance().refresh();
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
