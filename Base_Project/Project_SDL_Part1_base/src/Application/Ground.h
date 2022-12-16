#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include <vector>
#include "../Characters/Animals/Animal.h"

class Ground {
private:
    // Attention, NON-OWNING ptr, again to the screen
    SDL_Surface* window_surface_ptr_;

    // Attribute to store all the wolves and sheeps
    unsigned _nb_sheep;
    unsigned _nb_wolf;
    std::vector<std::shared_ptr<Animal>> animals;

public:
    // TODO: Ctor
    Ground(SDL_Surface* window_surface_ptr, unsigned n_sheep, unsigned n_wolf);

    // TODO: Dtor, again for clean up (if necessary)
    ~Ground(){};

    // TODO: Add an animal
    void add_animal(const std::shared_ptr<Animal>& animal);

    // TODO: "refresh the screen": Move animals and draw them
    // Possibly other methods, depends on your implementation
    void update();
};
