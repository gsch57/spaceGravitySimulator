#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <iostream>

#include "SDL2/SDL.h"

#define WIDTH 1500 // Screen width
#define HEIGHT 800 // Screen height

class Graphic
{
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Event event;

public:
    Graphic();
    ~Graphic();

    int init();
    int retrieveUserInteraction();
    SDL_Renderer *getRenderer() const { return m_renderer; };
    SDL_Window *getWindow() const { return m_window; };
    void cleanWindow() const;
    void refreshWindow(int delay) const;
};

#endif // __GRAPHIC_H__