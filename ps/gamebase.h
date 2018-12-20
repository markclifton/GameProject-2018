#pragma once

#include "managers/contextmanager.h"

namespace ps
{
class GameBase
{
public:
    GameBase();
    virtual ~GameBase();
    virtual void setup() = 0;
    void run();

    inline int getFPS() { return fps_; }

protected:
    inline void toggleFPSCounter() { fpsCounter_ = !fpsCounter_; }
    managers::ContextManager contextManager_;

private:
    bool fpsCounter_ {false};
    int fps_ {0};
};
}
