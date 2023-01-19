#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include <string>
#include <iostream>


#include "Ground.h"
#include "../Characters/Humans/Human.h"
#include "../Characters/Humans/Shepherd.h"
#include "../Characters/Animals/Dog.h"

// Definitions
constexpr double frame_rate = 60.0;             // Refresh rate
constexpr unsigned frame_width = 1200;          // Width of window in pixel
constexpr unsigned frame_height = 700;          // Height of window in pixel

// to the border of the screen
constexpr char path_img_grass[] = "../../media/grass.png";

class Application {
    private:
        SDL_Window* window_ptr_;
        SDL_Surface* window_surface_ptr_;
        SDL_Event window_event_;
        SDL_Surface *background_;

        std::unique_ptr<Ground> ground_;
        void print_background();
        SDL_Window *create_window();

        // Shepherd pointer
        std::shared_ptr<Shepherd> shepherd_ptr_;
        std::shared_ptr<Dog> dog_ptr_;


    public:
        Application(unsigned n_sheep, unsigned n_wolf); // Ctor
        ~Application();
        static void init();

        int loop(unsigned period);
        
        //Handle keyboard events to move the Shepherd
        void handle_keyboard_input(const std::shared_ptr<Shepherd> &shepherd_ptr);
};
