#pragma once

#include <vector>
#include "../Moving.h"
#include "../../SDL/Rendered.h"

class human : public Rendered
{
private:
public:
    // TODO: The constructor has to load the sdl_surface that corresponds to
    // the texture
    human(
        const std::string &file_path,
        SDL_Surface *window_surface_ptr,
        int human_height,
        int human_width,
        unsigned speed,
        ObjectType objectType,
        Point point

    );

    virtual void move(){};

    ObjectType type;

};