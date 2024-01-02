#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include <iostream>


class Game
{
    public:
        Game();
        ~Game();
        void init(const char* title, int w, int h, bool fullscreen);

        void handleEvents(double frameTime);
        void update(double frameTime);
        bool running()
        {
            return isRunning;
        }
        void render();
        void clean();

        static SDL_Renderer* renderer;
        static SDL_Event event;
        static bool isRunning;

    private:
        int cnt =0;
        SDL_Window *window;
};

#endif // GAME_H
