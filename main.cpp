#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#endif

#include "engine/game.h"

int main()
{
#ifdef _WIN32
    FreeConsole();
#endif

    Game g;
    g.run();
    return 0;
}
