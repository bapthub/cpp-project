#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdexcept>

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

protected:
    int _x;
    int _y;

    int _h_size;
    int _w_size;

    SDL_Surface* window_surface_ptr_;
    SDL_Surface* image_ptr_;
};


