
#include "Ground.h"
#include "../Characters/Animals/Sheep.h"
#include "../Characters/Animals/Wolf.h"
#include "../Characters/Animals/Dog.h"
#include "../Characters/Humans/Human.h"

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

    for (unsigned i = 0; i < n_sheep; ++i) {
        std::shared_ptr<Sheep> sheep = std::make_shared<Sheep>(window_surface_ptr_);
        add_animal(sheep);
        sheep->draw();
    }

    for (unsigned i = 0; i < n_wolf; ++i) {
        std::shared_ptr<Wolf> wolf = std::make_shared<Wolf>(window_surface_ptr_);
        add_animal(wolf);
        wolf->draw();
    }

    // Add the Sheperd Dog :
    std::shared_ptr<Dog> sheperd_dog = std::make_shared<Dog>(window_surface_ptr_);
    add_animal(sheperd_dog);
    sheperd_dog->draw();

}

void Ground::update() {
    // Clear all map to insert object with their new position
    map->clear();

    // Move characters
    std::for_each(animals.begin(), animals.end(),[this](const std::shared_ptr<Animal>& animal) {
        animal->move();
        map->add(*animal);
    });

    auto animals_cpy = animals;
    for (auto &animal : animals) {
        // Check if animal is a null ptr because it could have been deleted in case of collision
        if (animal == nullptr) {
            return;
        }

        // Check for collision in animal's area effect
        auto collisions = this->map->checkCollisions(*animal);
        for (auto& object: collisions) {
            animal->collide(*object, animals_cpy);
        }

        // Update animal state if a buff expires for example
        animal->updateState();

        // Remove animal because all collision with this animal are handles, we don't want this animal in further collision comparaisons
        map->removeObject(*animal);
    };
    animals = animals_cpy;

    // Render elements
    std::for_each(animals.begin(), animals.end(),[this](const std::shared_ptr<Animal>& animal) {
        animal->draw();
    });
    
    // Render Shepherd
    std::for_each(humans.begin(), humans.end(), [](std::shared_ptr<human> human)
                  { human->draw(); });
}

void Ground::order_sheperd_dog(int x, int y)
{
    for (auto &animal : animals) {
        if (animal->type == ObjectType::DOG) 
        {
            animal->setTarget(x, y);
        }
    }
}

void Ground::add_animal(const std::shared_ptr<Animal>& animal)
{
    animals.push_back(animal);
    map->add(*animal);
}

void Ground::add_human(const std::shared_ptr<human> &human)
{
    humans.push_back(human);
}