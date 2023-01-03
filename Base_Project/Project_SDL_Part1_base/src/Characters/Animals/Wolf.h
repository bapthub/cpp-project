#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include "Animal.h"
#include <string>

const std::string path_img_wolf = "./media/wolf.png";
const int wolf_height = 71;
const int wolf_width = 67;

class Wolf : public Animal {
public:
    explicit Wolf(SDL_Surface *window_surface_ptr);

    ~Wolf() override = default;

    void move() override;
};

