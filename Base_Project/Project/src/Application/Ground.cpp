
#include "Ground.h"
#include "../Characters/Animals/Sheep.h"
#include "../Characters/Animals/Wolf.h"

#include <SDL.h>
#include <memory>
#include <vector>
#include <unordered_set>
#include <iostream>

unsigned countDifferentAnimals(const std::vector<std::shared_ptr<Animal>>& animals)
{
    std::unordered_set<ObjectType> types;
    for (const auto& animal : animals) {
        types.insert(animal->type);
    }
    return types.size();
}

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
    // clear all map to insert object with their new position
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
        if (animal->updateState() == 1) {
            // if animal is dead, remove it from the list
            animals_cpy.erase(std::remove(animals_cpy.begin(), animals_cpy.end(), animal), animals_cpy.end());
        }

    };
    animals = animals_cpy;

    // render elements
    std::for_each(animals.begin(), animals.end(),[this](const std::shared_ptr<Animal>& animal) {
        animal->draw();
    });

    // render Shepherd
    std::for_each(humans.begin(), humans.end(), [](std::shared_ptr<human> human)
                  { human->draw(); });

    // if remain only dog and wolf or dog and sheep we terminate the game.
    if (countDifferentAnimals(animals) == 2)
    {
        std::cout << "Game ending" << std::endl;
        // Print the score wich is the number of animals left that of the Object type SHEEP
        std::cout << "Score: " << std::count_if(animals.begin(), animals.end(), [](const std::shared_ptr<Animal>& animal) {
            return animal->type == ObjectType::SHEEP;
        }) << std::endl;
        SDL_Quit();
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

