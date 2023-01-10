#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include "Animal.h"
#include <string>

const std::string path_img_sheperd = "../media/sheperd.png";
const int sheperd_height = 64;
const int sheperd_width = 64;

class Sheperd : public Animal {
public:
    explicit Sheperd(SDL_Surface *window_surface_ptr);

    void move() override;
};