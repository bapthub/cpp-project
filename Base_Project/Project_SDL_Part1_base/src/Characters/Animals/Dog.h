#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include "Animal.h"
#include <string>

const std::string path_img_sheperd = "../media/dog.png";
const int dog_height = 64;
const int dog_width = 64;

class Dog : public Animal {
public:
    explicit Dog(SDL_Surface *window_surface_ptr);

    void move() override;
};