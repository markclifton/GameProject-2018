#include "gamebase.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils/timer.h"
#include "managers/windowmanager.h"

namespace ps
{
GameBase::GameBase()
    : contextManager_()
{
}

GameBase::~GameBase()
{
    contextManager_.reset();

}

void GameBase::run()
{
    int ticks = 0;
    while( !WindowManager::Get().shouldClose() )
    {
        if( fpsCounter_ && ticks++ > 500)
        {
            fps_ = static_cast<int>(1.0/(WindowManager::Get().latency()*1000));
            ticks = 0;
        }

        contextManager_.run();
        WindowManager::Get().refresh();
    }
}
}
