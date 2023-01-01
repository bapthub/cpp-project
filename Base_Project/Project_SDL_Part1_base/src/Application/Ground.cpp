
#include "Ground.h"
#include "../Characters/Animals/Sheep.h"
#include "../Characters/Animals/Wolf.h"

#include <SDL.h>
#include <memory>
#include <vector>

Ground::Ground(SDL_Surface* window_surface_ptr, unsigned n_sheep, unsigned n_wolf)
{
    window_surface_ptr_ = window_surface_ptr;
    this->_nb_sheep = n_sheep;
    this->_nb_wolf = n_wolf;

    for (int i = 0; i < n_sheep; ++i) {
        std::shared_ptr<Sheep> sheep = std::make_shared<Sheep>(window_surface_ptr_);
        add_animal(sheep);
        sheep->draw();
    }

    for (int i = 0; i < n_wolf; ++i) {
        std::shared_ptr<Wolf> wolf = std::make_shared<Wolf>(window_surface_ptr_);
        add_animal(wolf);
        wolf->draw();
    }

}

void Ground::update() {
    std::for_each(animals.begin(), animals.end(),[](const std::shared_ptr<Animal>& animal) {
        animal->move();
        animal->draw();
    });
}

void Ground::add_animal(const std::shared_ptr<Animal>& animal)
{
    animals.push_back(animal);
}
