
#include "Ground.h"
#include "../Characters/Animals/Sheep.h"
#include "../Characters/Animals/Wolf.h"

#include <SDL.h>
#include <memory>
#include <vector>
#include <iostream>

#include "./Point.h"

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
//     clear all map to insert object with their new position
    map->clear();

    // move characters
    std::for_each(animals.begin(), animals.end(),[this](const std::shared_ptr<Animal>& animal) {
        animal->move();
        map->add(*animal);
    });

    auto animals_cpy = animals;
    for (auto &animal : animals) {
        //check if animal is a null ptr because it could have been deleted in case of collision
        if (animal == nullptr) {
            return;
        }

        // check for collision in animal's area effect
        auto collisions = this->map->checkCollisions(*animal);
        for (auto& object: collisions) {
            animal->collide(*object, animals_cpy);
        }

        // update animal state if a buff expires for example
        animal->updateState();

        // remove animal because all collision with this animal are handles, we don't want this animal in further collision comparaisons
        map->removeObject(*animal);
    };
    animals = animals_cpy;

    // render elements
    std::for_each(animals.begin(), animals.end(),[this](const std::shared_ptr<Animal>& animal) {
        animal->draw();
    });
}

void Ground::add_animal(const std::shared_ptr<Animal>& animal)
{
    animals.push_back(animal);
    map->add(*animal);
}



