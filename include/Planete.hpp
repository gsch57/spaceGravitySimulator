#include "SDL_render.h"
#include <vector>
#ifndef __PLANETE_H__
#define __PLANETE_H__

class Planete
{
private:
    int32_t m_positionX;
    int32_t m_positionY;
    double m_mass;
    double m_velocityX;
    double m_velocityY;
    double m_radius;
    SDL_Renderer *m_renderer;

public:
    Planete(SDL_Renderer *renderer,
            int32_t positionX,
            int32_t positionY,
            double mass,
            double velocityX,
            double velocityY,
            double radius);
    ~Planete();
    void draw() const;
    void computePosition(Planete *planete);
};

#endif // __PLANETE_H__