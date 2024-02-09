
#include <cmath>
#include <iostream>
#include "Planete.hpp"
#include "Graphic.hpp"
#include <vector>
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

int main(int argc, char *argv[])
{
    Graphic *sdl = new Graphic;
    SDL_Renderer *renderer = nullptr;

    if (sdl->init() < 0)
    {
        delete sdl;
        return -1;
    }
    renderer = sdl->getRenderer();
    bool finish = false;

    double sunSize = 139100.0; // in KM
    double earthSize = 12756;  // in KM
    double distance = 900000;
    // Taille de l'écran en km (échelle choisie)
    double screen_scale = 1500.0;

    // Calcul du diamètre réel du Soleil en pixels
    double sun_size_by_scale = (1500.0 / WIDTH) * sunSize;

    // Calcul du facteur d'échelle pour le rayon du Soleil
    double facteurEchelle = sun_size_by_scale / 50.0;

    std::vector<Planete *> planetes;

    // Initialisation des planètes avec l'échelle de masse
    Planete *soleil = new Planete(renderer, WIDTH / 2, HEIGHT / 2, 198900000, 0, 0, sunSize / facteurEchelle, {255, 255, 0, 255}); // Soleil (masse en kg)
    Planete *terre = new Planete(renderer, 100, HEIGHT / 2, 19320.7, 0, 52910, 10, {0, 255, 0, 255});                              // Terre (masse en kg, vitesse en m/s)
    Planete *yolo = new Planete(renderer, 99, HEIGHT / 2 + 5, 19320.7, 0, 0, 4, {50, 125, 255, 255});
    /* initialize random seed: */
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        planetes.push_back(new Planete(renderer, rand() % WIDTH + 1, rand() % HEIGHT + 1, rand() % 19890000 + 1000, 0, rand() % 5000 - 5000, 4, {Uint8(rand() % 255), Uint8(rand() % 255), Uint8(rand() % 255), 255}));
    }
    planetes.push_back(yolo);
    planetes.push_back(terre);
    planetes.push_back(soleil);
    double factor = 1;
    bool start = false;
    while (!finish)
    {
        sdl->cleanWindow();
        int action = sdl->retrieveUserInteraction();
        if (action == -1)
            finish = true;
        if (action == 1)
            start = !start;
        int index = 0;
        for (int i = 0; i < 300; i++)
        {
            for (int index = 0; index < planetes.size() - 1; index++)
            {
                if (i == 0)
                    planetes[index]->clearTrajectory();
                planetes[index]->computePosition(planetes, 0.0000002, index, i == 0 && start ? false : true);
            }
            for (int index = 0; index < planetes.size() - 1; index++)
                planetes[index]->addToTrajectory();
        }
        for (int index = 0; index < planetes.size(); index++)
            planetes[index]->draw();
        for (int index = 0; index < planetes.size(); index++)
            if (planetes[index]->needDelete(WIDTH, HEIGHT))
                planetes.erase(planetes.begin() + index);
        // Show the renderered frame
        sdl->refreshWindow(10);
    }
    return 0;
}