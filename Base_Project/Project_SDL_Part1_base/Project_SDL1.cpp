// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.

#include "Project_SDL1.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>

void init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
        throw std::runtime_error("init():" + std::string(SDL_GetError()));

    // Initialize SDL window
    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;

    // Create a window, use frame_width and frame_height, frame_boundary
    SDL_Window* window_ptr = SDL_CreateWindow
        ("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
         400, 400, flags);
    // SDL_Window* window_ptr = SDL_CreateWindow
    //     ("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    //      frame_width, frame_height, flags);

    SDL_Surface * surf = SDL_GetWindowSurface(window_ptr);

    // We must call SDL_CreateRenderer in order for draw calls to affect this window.
    SDL_Renderer* renderer = SDL_CreateRenderer(window_ptr, -1, 0);

    // Select the color for drawing. It is set to green here.
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    // Clear the entire screen to our selected color.
    SDL_RenderClear(renderer);

    // Up until now everything was drawn behind the scenes.
    // This will show the new, red contents of the window.
    SDL_RenderPresent(renderer);

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
        throw std::runtime_error("init(): SDL_image could not initialize! "
                                 "SDL_image Error: " +
                                 std::string(IMG_GetError()));


    SDL_Surface *image = IMG_Load("../../media/sheep.png");

    int return_val = SDL_BlitSurface(image,NULL,surf,NULL);
    std::cout << "return_val: " << return_val << std::endl;


    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);


    SDL_UpdateWindowSurface(window_ptr);

    // show image for 5 seconds
    SDL_Delay(5000);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window_ptr);
}

namespace {
    // Defining a namespace without a name -> Anonymous workspace
    // Its purpose is to indicate to the compiler that everything
    // inside of it is UNIQUELY used within this source file.

    SDL_Surface* load_surface_for(const std::string& path,
                              SDL_Surface* window_surface_ptr) {

        SDL_Surface* surface = IMG_Load(path.c_str());
        if (surface == NULL) {
            throw std::runtime_error("can't load surface");
        }

        SDL_Surface* formattedSurface = SDL_ConvertSurface(surface, window_surface_ptr->format, 0);
        if (formattedSurface == NULL) {
            throw std::runtime_error("can't format surface");
        }

        SDL_FreeSurface(surface);

        return formattedSurface;
        // Helper function to load a png for a specific surface
        // See SDL_ConvertSurface
    }

//    get_random_dir(unsigned speed)


} // namespace

animal::animal(const std::string &file_path, SDL_Surface *window_surface_ptr) {
    this->window_surface_ptr_ = window_surface_ptr;
    this->image_ptr_ = load_surface_for(file_path, window_surface_ptr);
    this->_y = random() % window_surface_ptr->h;
    this->_x = random() * window_surface_ptr->w;
}

animal::~animal() {
    SDL_FreeSurface(this->image_ptr_);
    this->image_ptr_ = nullptr;
}

unsigned animal::getX() const {
    return _x;
}

unsigned animal::getY() const {
    return _y;
}


// void sheep::move(SDL_Surface *window_surface_ptr) {
//     this->_x = 0;
//     this->_y = 0;
// }

// void wolf::move(SDL_Surface *window_surface_ptr) {
//     this->_x = 0;
//     this->_y = 0;
// }

sheep::sheep(SDL_Surface *window_surface_ptr): animal("../media/sheep.png" , window_surface_ptr) {
    this->_h_size = 71;
    this->_w_size = 67;
}

wolf::wolf(SDL_Surface *window_surface_ptr) : animal("../media/wolf.png", window_surface_ptr) {
    this->_h_size = 42;
    this->_w_size = 62;
}
