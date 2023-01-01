#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include <vector>
#include <map>
#include <list>
#include "../Characters/Animals/Animal.h"

class Ground {
private:
    // Attention, NON-OWNING ptr, again to the screen
    SDL_Surface* window_surface_ptr_;

    unsigned _nb_sheep;
    unsigned _nb_wolf;
    std::vector<std::shared_ptr<Animal>> animals;

    unsigned cellSize;
    std::map<int, std::list<std::shared_ptr<Animal>>> spatialHashMap;

public:
    Ground(SDL_Surface* window_surface_ptr, unsigned n_sheep, unsigned n_wolf);

    ~Ground(){};

    void add_animal(const std::shared_ptr<Animal>& animal);

    void update();

};
