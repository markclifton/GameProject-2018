#include "game.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "shaders/shader.h"
#include "utils/keyhandler.h"
#include "utils/mousehandler.h"
#include "utils/timer.h"

Game::Game()
    : m_contextManager()
    , m_windowManager()
    , m_camera(new Camera())
{
    m_camera->SetViewport(0, 0, 640, 480);

    m_windowManager.toggleVsync(false);
    m_windowManager.registerHandler(std::make_unique<utils::KeyHandler>(m_camera.get()));
    m_windowManager.registerHandler(std::make_unique<utils::MouseHandler>());

    setup();
}

void Game::run()
{
    Shader s("resources/basic.vs", "resources/basic.fs");
    s.enableAttribArray("position");
    s.enableAttribArray("color");

    glm::mat4 p, v;
    m_camera->Update();
    m_camera->GetMatricies(p, v);
    s.setUniform("projection", p);

    utils::Timer t;
    int ticks = 0;
    while( !m_windowManager.shouldClose() )
    {
        if( ticks++ > 500)
        {
            std::cerr << 1.0/(t.reset()/ticks) << "\n";
            ticks = 0;
        }

        m_camera->Update();
        m_camera->GetMatricies(p, v);
        s.setUniform("view", v);

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
