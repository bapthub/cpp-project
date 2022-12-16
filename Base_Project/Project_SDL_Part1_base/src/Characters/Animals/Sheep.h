#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include "Animal.h"
#include <string>

const std::string path_img_sheep = "../media/sheep.png";

class Sheep : public Animal {
public:
    explicit Sheep(SDL_Surface *window_surface_ptr): Animal(path_img_sheep, window_surface_ptr, 71, 67, 1) {}

    virtual void move() override;
};
