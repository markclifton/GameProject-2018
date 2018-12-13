#include "game.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "shaders/shader.h"
#include "utils/mousehandler.h"
#include "utils/timer.h"

Game::Game()
    : m_contextManager()
{
    m_windowManager.toggleVsync(false);
    setup();
}

Game::~Game()
{
    m_contextManager.reset();
    m_shaderManager.reset();
    m_textureManager.reset();
    m_windowManager.close();
}

void Game::run()
{
    int ticks = 0;
    while( !m_windowManager.shouldClose() )
    {
        if( ticks++ > 500)
        {
           // std::cerr << m_windowManager.latency()*1000 << "ms\n";
            ticks = 0;
        }

        m_contextManager.run();
        m_windowManager.refresh();
    }
}

void Game::setup()
{
    if( !m_contextManager.addContext("Sandbox", std::make_unique<Context>(m_soundManager, m_shaderManager, m_textureManager, m_windowManager)) )
        std::cerr << "Failed to add context\n";
    if( !m_contextManager.setContext("Sandbox") )
        std::cerr << "Failed to set context\n";
}
