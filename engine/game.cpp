#include "game.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "shaders/shader.h"
#include "utils/timer.h"

namespace ps
{
Game::Game()
    : contextManager_()
{
    setup();
    run();
}

Game::~Game()
{
    contextManager_.reset();
    managers::WindowManager::Get().close();
}

void Game::setup()
{
}

void Game::run()
{
    int ticks = 0;
    while( !managers::WindowManager::Get().shouldClose() )
    {
        if( fpsCounter_ && ticks++ > 500)
        {
            std::cerr << managers::WindowManager::Get().latency()*1000 << "ms\n";
            ticks = 0;
        }

        contextManager_.run();
        managers::WindowManager::Get().refresh();
    }
}
}
