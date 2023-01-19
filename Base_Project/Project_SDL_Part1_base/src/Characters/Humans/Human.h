#pragma once

#include <vector>
#include "../Moving.h"
#include "../../SDL/Rendered.h"

class human : public Rendered
{
private:
public:
    human(
        const std::string &file_path,
        SDL_Surface *window_surface_ptr,
        int human_height,
        int human_width,
        ObjectType objectType
    );

    virtual void move(){};

    ObjectType type;

};