#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "../Application/Point.h"

class Rendered {
private:
    SDL_Surface* load_surface_for(const std::string& path, SDL_Surface* window_surface_ptr);

public:
    Rendered(
            int x,
            int y,
            int h_size,
            int w_size,
            const std::string& file_path,
            SDL_Surface* window_surface_ptr
            );

    ~Rendered();

    void draw();

    Point point;

    int h_size;
    int w_size;

protected:

    SDL_Surface* window_surface_ptr_;
    SDL_Surface* image_ptr_;
};


