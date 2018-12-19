#pragma once

#include "managers/contextmanager.h"
#include "managers/soundmanager.h"
#include "managers/shadermanager.h"
#include "managers/texturemanager.h"
#include "managers/windowmanager.h"

namespace ps
{
class Game
{
public:
    Game();
    virtual ~Game();

protected:
    inline void toggleFPSCounter() { fpsCounter_ = !fpsCounter_; }
    virtual void setup();
    managers::ContextManager contextManager_;

private:
    void run();
    bool fpsCounter_ {false};
};
}
