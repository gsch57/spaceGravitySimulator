#include "../include/Planete.hpp"

Planete::Planete(SDL_Renderer *renderer, int32_t positionX,
                 int32_t positionY,
                 double mass,
                 double velocityX,
                 double velocityY,
                 double radius)
{
    m_positionX = positionX;
    m_positionY = positionY;
    m_mass = mass;
    m_velocityX = velocityX;
    m_velocityY = velocityY;
    m_radius = radius;
    m_renderer = renderer;
}

Planete::~Planete()
{
    m_renderer = nullptr;
}

void Planete::draw() const
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 250, 255);

    std::vector<SDL_Point> points;

    // 35 / 49 is a slightly biased approximation of 1/sqrt(2)
    const int arrSize = std::ceil((m_radius * 8 * 35 / 49) / 8.0) * 8.0;
    points.reserve(arrSize);

    const int32_t diameter = (m_radius * 2);

    int32_t x = (m_radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        // Each of the following renders an octant of the circle
        points.push_back({m_positionX + x, m_positionY - y});
        points.push_back({m_positionX + x, m_positionY + y});
        points.push_back({m_positionX - x, m_positionY - y});
        points.push_back({m_positionX - x, m_positionY + y});
        points.push_back({m_positionX + y, m_positionY - x});
        points.push_back({m_positionX + y, m_positionY + x});
        points.push_back({m_positionX - y, m_positionY - x});
        points.push_back({m_positionX - y, m_positionY + x});

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
    SDL_RenderDrawPoints(m_renderer, points.data(), points.size());
}
void Planete::computePosition(Planete *planete)
{
}