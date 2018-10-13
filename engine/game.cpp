#include "game.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    Shader s("resources/basic.vs", "resources/basic.fs");
    s.enableAttribArray("position");
    s.enableAttribArray("color");


    glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(90.f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
        4.0f / 3.0f,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
        0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
        100.0f             // Far clipping plane. Keep as little as possible.
    );
    s.setUniform("projection", projectionMatrix);

    utils::Timer t;
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
