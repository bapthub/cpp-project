#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include "Animal.h"
#include <string>

const std::string path_img_sheep = "./media/sheep.png";
const int sheep_height = 42;
const int sheep_width = 62;

class Sheep : public Animal {
public:
    explicit Sheep(SDL_Surface *window_surface_ptr);

    Sheep(SDL_Surface *window_surface_ptr, Point point);

    ~Sheep() override = default;

    void move() override;
};
