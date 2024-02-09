#include "Graphic.hpp"

Graphic::Graphic()
{
    SDL_Init(SDL_INIT_VIDEO);
    m_window = nullptr;
    m_renderer = nullptr;
}

Graphic::~Graphic()
{
    if (m_window != nullptr)
        SDL_DestroyWindow(m_window);
    if (m_renderer != nullptr)
        SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

int Graphic::init()
{
    m_window = SDL_CreateWindow(
        "Space Gravity Simulation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        0);

    if (m_window == NULL)
    {
        std::cerr << "Error: Unable to create window: " << SDL_GetError() << std::endl;
        return -1;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if (m_renderer == NULL)
    {
        std::cerr << "Error: Unable to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        return -1;
    }
    return 0;
}

int Graphic::retrieveUserInteraction()
{
    while (SDL_PollEvent(&event))
    {
        // if (SDL_MOUSEBUTTONDOWN)
        //  DrawCircle(renderer, event.button.x, event.button.y, 50);
        if (SDL_QUIT == event.type)
            return -1;
        if (SDL_KEYDOWN == event.type)
        {
            if (SDLK_ESCAPE == event.key.keysym.sym)
                return -1;
            if (SDLK_SPACE == event.key.keysym.sym)
                return 1;
        }
    }
    return 0;
}

void Graphic::cleanWindow() const
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); // m_renderer, r, g, b, a
    SDL_RenderClear(m_renderer);
}

void Graphic::refreshWindow(int delay) const
{
    SDL_RenderPresent(m_renderer);
    SDL_Delay(delay);
}
