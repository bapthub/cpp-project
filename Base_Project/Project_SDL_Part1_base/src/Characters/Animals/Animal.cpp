#include "Animal.h"
#include "../../Application/Application.h"

Animal::Animal(
        const std::string& file_path,
        SDL_Surface* window_surface_ptr,
        int animal_height,
        int animal_width,
        unsigned speed
):
        Moving(speed),
        Rendered(
                (random() % (frame_height - h_size)),
                (random() % (frame_width - w_size)),
                animal_height,
                animal_width,
                file_path,
                window_surface_ptr
        ) {};
