#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include <string>
#include <stdexcept>

#include "Ground.h"

// Definitions
constexpr double frame_rate = 60.0;             // Refresh rate
constexpr double frame_time = 1. / frame_rate;  // Time per frame
constexpr unsigned frame_width = 1400;          // Width of window in pixel
constexpr unsigned frame_height = 900;          // Height of window in pixel
constexpr unsigned frame_boundary = 100;        // Minimal distance of animals
// to the border of the screen
constexpr char path_img_grass[] = "../media/grass.png";

class Application {
    private:
        // The following are OWNING ptrs
        SDL_Window* window_ptr_;
        SDL_Surface* window_surface_ptr_;
        SDL_Event window_event_;
        SDL_Surface *background_;

        std::unique_ptr<Ground> ground_;
        void print_background();
        SDL_Window *create_window();

    public:
        Application(unsigned n_sheep, unsigned n_wolf); // Ctor
        ~Application();
        static void init();

        int loop(unsigned period);
};
