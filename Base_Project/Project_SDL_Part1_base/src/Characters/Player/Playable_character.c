#include "Playable_character.h"
#include "../../Application/Application.h"

Playable_character::Playable_character(
        const std::string& file_path,
        SDL_Surface* window_surface_ptr,
        int character_height,
        int character_width,
        unsigned speed
):
        Moving(speed),
        Rendered(
                (random() % (frame_height - _h_size)),
                (random() % (frame_width - _w_size)),
                character_height,
                character_height,
                file_path,
                window_surface_ptr
        ) {};
