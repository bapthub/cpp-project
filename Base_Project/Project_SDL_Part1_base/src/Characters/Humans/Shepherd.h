
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include "Human.h"
#include <string>

const std::string path_img_shepherd = "../../media/shepherd.png";

class Shepherd : public human
{
public:
    static const int SHEPHERD_HEIGHT = 67;
    static const int SHEPHERD_WIDTH = 90;

    explicit Shepherd(SDL_Surface *window_surface_ptr);
    ~Shepherd() override = default;

    void move(int x_offset, int y_offset);

};