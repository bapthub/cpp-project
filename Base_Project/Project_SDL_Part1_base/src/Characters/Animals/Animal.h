#pragma once

#include "../Moving.h"
#include "../../SDL/Rendered.h"

class Animal: public Moving, public Rendered {
private:
public:
    Animal(
            const std::string& file_path,
            SDL_Surface* window_surface_ptr,
            int animal_height,
            int animal_width,
            unsigned speed
            );

protected:
    unsigned time_to_change = 0;
};
