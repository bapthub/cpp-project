#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <memory>

class Animal {
private:
    SDL_Surface* window_surface_ptr_;
    // Ptr to the surface on which we want the
    // Animal to be drawn, also non-owning

    SDL_Surface* image_ptr_;
    // The texture of the Sheep (the loaded image), use load_surface_for

public:
    Animal(
            const std::string& file_path,
            SDL_Surface* window_surface_ptr,
            int animal_height,
            int animal_width,
            unsigned speed
            );

    ~Animal();

    void draw();

    virtual void move(){};

    unsigned getX() const;

    unsigned getY() const;

protected:
    int _x;
    int _y;

    int _h_size;
    int _w_size;

    unsigned time_to_change;

    unsigned _x_dir = 0;
    unsigned _y_dir = 0;

    unsigned speed;

    void get_next_pos();
};
