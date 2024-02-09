#include <vector>
#include "SDL2/SDL.h"
#ifndef __PLANETE_H__
#define __PLANETE_H__

constexpr double G = 1;
class Planete
{
private:
    double m_positionX;
    double m_positionY;
    double m_trajectoryPositionX;
    double m_trajectoryPositionY;
    double m_mass;
    double m_velocityX;
    double m_velocityY;
    double m_trajectoryVelocityX;
    double m_trajectoryVelocityY;
    double m_radius;
    double m_accelerationX;
    double m_accelerationY;
    SDL_Renderer *m_renderer;
    std::vector<SDL_Point> m_trajectory;
    SDL_Color m_color;

public:
    Planete(SDL_Renderer *renderer,
            double positionX,
            double positionY,
            double mass,
            double velocityX,
            double velocityY,
            double radius,
            SDL_Color color);
    ~Planete();
    void draw() const;
    void computePosition(std::vector<Planete *> planetes, double timeStep, int indexThis, bool isTrajectoryCompute);
    void updateVelocityX(double velo);
    void clearTrajectory();
    void addToTrajectory();
    void updateVelocityY(double velo);
    bool needDelete(int WIDTH, int HEIGTH) const;
};

#endif // __PLANETE_H__