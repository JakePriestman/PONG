#include <iostream>
#include "SDL2/SDL.h"
#include "Game.h"


Game *game = nullptr;


int main(int argc, char *argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    double frameStart;
    double frameEnd;
    double frameTime;
    srand(SDL_GetTicks());

    game = new Game();

    game->init("PONG",800,600,false);

    while(game->running())
    {
        frameStart = frameEnd;
        frameEnd = SDL_GetTicks();
        frameTime = (frameEnd - frameStart)/1000.0;

        game->handleEvents(frameTime);
        game->update(frameTime);
        game->render();

    }
    game->clean();
    return 0;
}
