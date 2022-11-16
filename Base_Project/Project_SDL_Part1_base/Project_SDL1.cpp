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

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
        throw std::runtime_error("init(): SDL_image could not initialize! "
                                 "SDL_image Error: " +
                                 std::string(IMG_GetError()));
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
    SDL_Window *create_window()
    {
        // Initialize SDL window
        Uint32 flags = SDL_WINDOW_SHOWN | SDL_QUIT;

        // Create a window, use frame_width and frame_height, frame_boundary
        SDL_Window* window_ptr = SDL_CreateWindow
            ("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
             frame_width, frame_height, flags);
        return window_ptr;
    }

    SDL_Renderer *create_render(SDL_Window *window_ptr)
    {
        // We must call SDL_CreateRenderer in order for draw calls to affect this window.
        SDL_Renderer* renderer = SDL_CreateRenderer(window_ptr, -1, 0);

        // Select the color for drawing. It is set to green here.
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        // Clear the entire screen to our selected color.
        SDL_RenderClear(renderer);

        // Up until now everything was drawn behind the scenes.
        // This will show the new, red contents of the window.
        SDL_RenderPresent(renderer);
        return renderer;
    }

//    get_random_dir(unsigned speed)
} // namespace

application::application(unsigned n_sheep, unsigned n_wolf)
{
    window_ptr_ = create_window();
    if (window_ptr_ == nullptr)
        throw std::runtime_error("application(): " + std::string(SDL_GetError()));

    window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);
    // SDL_Renderer *renderer = create_render(window_ptr);

    SDL_Surface *image = IMG_Load("../media/grass.png");
    SDL_Surface* formatted_image = SDL_ConvertSurface(image, window_surface_ptr_->format, 0);
        if (formatted_image == NULL) {
            throw std::runtime_error("can't format surface");
        }

    SDL_FreeSurface(image);

    // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    //SDL_Rect img_rect{0, 0, 200, 200};

    // int rec = SDL_RenderDrawRect(renderer,&img_rect);
    // std::cout << "rec: " << rec << std::endl;
    
    int return_val = SDL_BlitSurface(formatted_image,NULL,window_surface_ptr_ ,NULL);
    std::cout << "return_val: " << return_val << std::endl;

    // SDL_RenderCopy(renderer, texture, NULL, &img_rect);
    // SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window_ptr_);

    ground_ = new ground(window_surface_ptr_, n_sheep, n_wolf);
}

int application::loop(unsigned window_time)
{
    // show image for 5 seconds


    while(SDL_GetTicks() < window_time * 1000) {

    }
    // SDL_DestroyTexture(texture);

    return 0;
}

application::~application()
{
    SDL_FreeSurface(window_surface_ptr_);
    // SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window_ptr_);
    //free IMAGES
}

ground::ground(SDL_Surface* window_surface_ptr, unsigned n_sheep, unsigned n_wolf)
{
    window_surface_ptr_ = window_surface_ptr;
    for (int i = 0; i < n_sheep; ++i) {
        std::shared_ptr<Sheep> sheep = std::make_shared<Sheep>(window_surface_ptr_);
        add_animal(sheep);
        sheep->draw();
    }
    for (int i = 0; i < n_wolf; ++i) {
        std::shared_ptr<Wolf> wolf =std::make_shared<Wolf>(window_surface_ptr_);
        add_animal(wolf);
        wolf->draw();
    }
}

void ground::add_animal(const std::shared_ptr<animal>& animal)
{
    animals.push_back(animal);
}
 
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

void animal::draw() {

    SDL_Rect img_rect{_x, _y, _h_size, _w_size};

    if(SDL_BlitSurface(image_ptr_,NULL,window_surface_ptr_ ,&img_rect)) {
        throw std::runtime_error("cannot draw animal");
    }
}


// void Sheep::move(SDL_Surface *window_surface_ptr) {
//     this->_x = 0;
//     this->_y = 0;
// }

// void Wolf::move(SDL_Surface *window_surface_ptr) {
//     this->_x = 0;
//     this->_y = 0;
// }

Sheep::Sheep(SDL_Surface *window_surface_ptr): animal("../media/Sheep.png" , window_surface_ptr) {
    this->_h_size = 71;
    this->_w_size = 67;
}

Wolf::Wolf(SDL_Surface *window_surface_ptr) : animal("../media/Wolf.png", window_surface_ptr) {
    this->_h_size = 42;
    this->_w_size = 62;
}
