#pragma once

#include "Animal.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <memory>

const std::string path_img_sheperd_dog = "../media/sheperd_dog.png";
const int sheperd_dog_height = 64;
const int sheperd_dog_width = 64;

class Sheperd_dog : public Animal {
public:
    explicit Sheperd_dog(SDL_Surface *window_surface_ptr);

    void move() override;
};