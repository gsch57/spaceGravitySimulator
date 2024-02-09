#include "../include/Planete.hpp"
#include <iostream>

Planete::Planete(SDL_Renderer *renderer, double positionX,
                 double positionY,
                 double mass,
                 double velocityX,
                 double velocityY,
                 double radius,
                 SDL_Color color)
{
    m_positionX = positionX;
    m_positionY = positionY;
    m_trajectoryPositionX = positionX;
    m_trajectoryPositionY = positionY;
    m_mass = mass;
    m_velocityX = velocityX;
    m_velocityY = velocityY;
    m_trajectoryVelocityX = velocityX;
    m_trajectoryVelocityY = velocityY;
    m_radius = 100 * std::log10(1 + (mass / 198900000)) + 5;
    m_renderer = renderer;
    m_accelerationX = 0.0;
    m_accelerationY = 0.0;
    m_color = color;
}

bool Planete::needDelete(int WIDTH, int HEIGTH) const
{
    if (m_positionX < -200 || m_positionX > WIDTH + 200)
        return true;
    if (m_positionY < -200 || m_positionY > HEIGTH + 200)
        return true;
}

Planete::~Planete()
{
    std::cout << "delete Planete" << std::endl;
    m_renderer = nullptr;
}

void Planete::draw() const
{
    SDL_SetRenderDrawColor(m_renderer, m_color.r, m_color.g, m_color.b, m_color.a);

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
        points.push_back({static_cast<int>(m_positionX) + x, static_cast<int>(m_positionY) - y});
        points.push_back({static_cast<int>(m_positionX) + x, static_cast<int>(m_positionY) + y});
        points.push_back({static_cast<int>(m_positionX) - x, static_cast<int>(m_positionY) - y});
        points.push_back({static_cast<int>(m_positionX) - x, static_cast<int>(m_positionY) + y});
        points.push_back({static_cast<int>(m_positionX) + y, static_cast<int>(m_positionY) - x});
        points.push_back({static_cast<int>(m_positionX) + y, static_cast<int>(m_positionY) + x});
        points.push_back({static_cast<int>(m_positionX) - y, static_cast<int>(m_positionY) - x});
        points.push_back({static_cast<int>(m_positionX) - y, static_cast<int>(m_positionY) + x});

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
    SDL_SetRenderDrawColor(m_renderer, m_color.r, m_color.g, m_color.b, m_color.a - 100);
    SDL_RenderDrawPoints(m_renderer, m_trajectory.data(), m_trajectory.size());
}

void Planete::updateVelocityX(double velo)
{
    m_velocityX += velo;
    std::cout << m_velocityX << std::endl;
}

void Planete::updateVelocityY(double velo)
{
    m_velocityY += velo;
    std::cout << m_velocityY << std::endl;
}

void Planete::clearTrajectory()
{
    m_trajectory.clear();
    m_trajectoryPositionX = m_positionX;
    m_trajectoryPositionY = m_positionY;
    m_trajectoryVelocityX = m_velocityX;
    m_trajectoryVelocityY = m_velocityY;
}

void Planete::addToTrajectory()
{
    m_trajectory.push_back({static_cast<int>(m_trajectoryPositionX), static_cast<int>(m_trajectoryPositionY)});
}

void Planete::computePosition(std::vector<Planete *> planetes, double timeStep, int indexThis, bool isTrajectoryCompute = true)
{
    double k1x, k1y, k2x, k2y, k3x, k3y, k4x, k4y;
    double k1vx, k1vy, k2vx, k2vy, k3vx, k3vy, k4vx, k4vy;

    double velocityX = m_trajectoryVelocityX;
    double velocityY = m_trajectoryVelocityY;
    double positionX = m_trajectoryPositionX;
    double positionY = m_trajectoryPositionY;
    for (int j = 0; j < planetes.size(); j++)
    {
        if (j == indexThis)
            continue;
        Planete *planete = planetes[j];
        double dx1 = planete->m_positionX - positionX;
        double dy1 = planete->m_positionY - positionY;

        double distanceSquared1 = dx1 * dx1 + dy1 * dy1;
        double distance1 = sqrt(distanceSquared1);

        double forceMagnitude1 = (G * m_mass * planete->m_mass) / distanceSquared1;
        double accelerationX1 = forceMagnitude1 * dx1 / distance1;
        double accelerationY1 = forceMagnitude1 * dy1 / distance1;
        k1x = velocityX;
        k1y = velocityY;
        k1vx = accelerationX1;
        k1vy = accelerationY1;

        // Calculate k2
        double newX2 = positionX + k1x * 0.5 * timeStep;
        double newY2 = positionY + k1y * 0.5 * timeStep;
        double dx2 = planete->m_positionX - newX2;
        double dy2 = planete->m_positionY - newY2;
        double distanceSquared2 = dx2 * dx2 + dy2 * dy2;
        double distance2 = sqrt(distanceSquared2);
        double forceMagnitude2 = (G * m_mass * planete->m_mass) / distanceSquared2;
        double accelerationX2 = forceMagnitude2 * dx2 / distance2;
        double accelerationY2 = forceMagnitude2 * dy2 / distance2;
        k2x = velocityX + 0.5 * timeStep * k1vx;
        k2y = velocityY + 0.5 * timeStep * k1vy;
        k2vx = accelerationX2;
        k2vy = accelerationY2;

        double newX3 = positionX + k2x * 0.5 * timeStep;
        double newY3 = positionY + k2y * 0.5 * timeStep;
        double dx3 = planete->m_positionX - newX3;
        double dy3 = planete->m_positionY - newY3;
        double distanceSquared3 = dx3 * dx3 + dy3 * dy3;
        double distance3 = sqrt(distanceSquared3);
        double forceMagnitude3 = (G * m_mass * planete->m_mass) / distanceSquared3;
        double accelerationX3 = forceMagnitude3 * dx3 / distance3;
        double accelerationY3 = forceMagnitude3 * dy3 / distance3;
        k3x = velocityX + 0.5 * timeStep * k2vx;
        k3y = velocityY + 0.5 * timeStep * k2vy;
        k3vx = accelerationX3;
        k3vy = accelerationY3;

        double newX4 = positionX + k3x * timeStep;
        double newY4 = positionY + k3y * timeStep;
        double dx4 = planete->m_positionX - newX4;
        double dy4 = planete->m_positionY - newY4;
        double distanceSquared4 = dx4 * dx4 + dy4 * dy4;
        double distance4 = sqrt(distanceSquared4);
        double forceMagnitude4 = (G * m_mass * planete->m_mass) / distanceSquared4;
        double accelerationX4 = forceMagnitude4 * dx4 / distance4;
        double accelerationY4 = forceMagnitude4 * dy4 / distance4;
        k4x = velocityX + timeStep * k3vx;
        k4y = velocityY + timeStep * k3vy;
        k4vx = accelerationX4;
        k4vy = accelerationY4;

        // Update position and velocity using RK4 formulas
        positionX += (timeStep / 6.0) * (k1x + 2.0 * k2x + 2.0 * k3x + k4x);
        positionY += (timeStep / 6.0) * (k1y + 2.0 * k2y + 2.0 * k3y + k4y);
        velocityX += (timeStep / 6.0) * (k1vx + 2.0 * k2vx + 2.0 * k3vx + k4vx);
        velocityY += (timeStep / 6.0) * (k1vy + 2.0 * k2vy + 2.0 * k3vy + k4vy);
    }
    if (!isTrajectoryCompute)
    {
        m_positionX = positionX;
        m_positionY = positionY;
        m_velocityX = velocityX;
        m_velocityY = velocityY;
    }
    // Add position to trajectory
    m_trajectoryPositionX = positionX;
    m_trajectoryPositionY = positionY;
    m_trajectoryVelocityX = velocityX;
    m_trajectoryVelocityY = velocityY;
}