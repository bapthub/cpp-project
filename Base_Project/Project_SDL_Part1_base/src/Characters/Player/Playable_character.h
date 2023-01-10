#pragma once

#include "../Moving.h"
#include "../../SDL/Rendered.h"

class Playable_character: public Moving, public Rendered {
private:
public:
    Playable_character(
            const std::string& file_path,
            SDL_Surface* window_surface_ptr,
            int character_height,
            int character_width,
            unsigned speed
            );

protected:
    unsigned time_to_change = 0;
};
