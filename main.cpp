#include "SDL2/SDL.h"
#include <cmath>
#include <iostream>

#define WIDTH 800  // Screen width
#define HEIGHT 600 // Screen height

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = NULL;

    window = SDL_CreateWindow(
        "Space Gravity Simulation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        0);

    if (window == NULL)
    {
        std::cerr << "Error: Unable to create window: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer *renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        std::cerr << "Error: Unable to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return -1;
    }

    SDL_Event event;
    bool finish = false;

    while (!finish)
    {
        while (SDL_PollEvent(&event))
        {
            if (SDL_QUIT == event.type)
                finish = true;
        }
        SDL_Delay(100);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}