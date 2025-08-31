#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

#include "convexhull.h"

class SDLDriver
{
    public:
        int windowWidth, windowHeight, pixelSize;
        SDLDriver(int windowWidth, int windowHeight, int pixelSize, const char *windowName);
        SDL_AppResult drive();

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
};