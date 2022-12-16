#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include "Animal.h"
#include <string>

const std::string path_img_wolf = "../media/wolf.png";

class Wolf : public Animal {
public:
    explicit Wolf(SDL_Surface *window_surface_ptr): Animal(path_img_wolf, window_surface_ptr, 42, 62, 1) {};

    void move() override;
};

