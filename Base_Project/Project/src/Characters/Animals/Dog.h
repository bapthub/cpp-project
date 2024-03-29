#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include "Animal.h"

const std::string path_img_dog = "../../media/sheperd_dog.png";
const int dog_height = 44;                  // The size of the dog
const int dog_width = 64;

class Dog : public Animal {
public:
    explicit Dog(SDL_Surface *window_surface_ptr);

    ~Dog() override = default;

    void move() override;

    std::shared_ptr<Animal> procreate(Animal &animal) override;

    void collide(Animal& animal, std::vector<std::shared_ptr<Animal>>& animals) override;

    void set_shepherd_position(int x, int y);
    std::pair<int, int> get_shepherd_position();
    void set_dog_target(int x, int y);
    std::pair<int, int> get_dog_target();
};
