#include "Game.h"

#ifdef _WIN32
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include <windows.h>
#endif

int main()
{
    Game game;
    game.run();

    return 0;
}
