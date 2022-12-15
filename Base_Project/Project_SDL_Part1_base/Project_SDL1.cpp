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
            ("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
             frame_width, frame_height, flags);
        return window_ptr;
    }
} // namespace

application::application(unsigned n_sheep, unsigned n_wolf)
{
    //Initialize SDL
//    if (SDL_Init(SDL_INIT_VIDEO) < 0)
//        throw std::runtime_error(std::string(SDL_GetError()));
//
//    //Initialize PNG loading
//    int imgFlags = IMG_INIT_PNG;
//    if (!(IMG_Init(imgFlags) & imgFlags))
//        throw std::runtime_error("SDL_image could not initialize! "
//                                 "SDL_image Error: " + std::string(IMG_GetError()));


//    auto window_ptr = SDL_CreateWindow("SDL2 Window",
//                                       SDL_WINDOWPOS_CENTERED,
//                                       SDL_WINDOWPOS_CENTERED,
//                                       194, 259,
//                                       0);
//
//    if (!window_ptr)
//        throw std::runtime_error(std::string(SDL_GetError()));

//    auto window_surface_ptr = SDL_GetWindowSurface(window_ptr);
//
//    if (!window_surface_ptr)
//        throw std::runtime_error(std::string(SDL_GetError()));

//    auto surf = IMG_Load("../media/grass.png");
//    if (!surf)
//        throw std::runtime_error("Could not load image");
//    auto rect = SDL_Rect{0,0,194,259};
//    if (SDL_BlitSurface(surf, NULL, window_surface_ptr, &rect))
//        throw std::runtime_error("Could not apply texture.");
//
//
//    SDL_UpdateWindowSurface(window_ptr);

//    auto start = SDL_GetTicks();
//
//    SDL_Event e;
//    bool quit = false;
//    while (!quit && (SDL_GetTicks() - start < 10000)) {
//        while (SDL_PollEvent(&e)) {
//            if (e.type == SDL_QUIT) {
//                quit = true;
//                break;
//            }
//        }
//    }

    window_ptr_ = create_window();
    if (window_ptr_ == nullptr) {
        throw std::runtime_error("application(): " + std::string(SDL_GetError()));
    }


//
    window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);

    SDL_Surface *image = IMG_Load(path_img_grass);
    background_ = SDL_ConvertSurface(image, window_surface_ptr_->format, 0);

    SDL_FreeSurface(image);
    print_background();
    ground_ = std::make_unique<ground>(window_surface_ptr_, n_sheep, n_wolf);

    SDL_UpdateWindowSurface(window_ptr_);

}

void application::print_background()
{    
    if(SDL_BlitSurface(background_,NULL,window_surface_ptr_ ,NULL) < 0)
    {
        throw std::runtime_error("can't blit surface");
    }
}
int application::loop(unsigned window_time)
{
    unsigned start = SDL_GetTicks();
    while (SDL_GetTicks() - start < window_time * 1000)
    {
        if (SDL_PollEvent(&window_event_))
        {
            if (window_event_.type == SDL_QUIT)
            {
                // If SDL_QUIT event is triggered, exit the loop
                break;
            }
        }
        print_background();
        ground_->update();
        SDL_UpdateWindowSurface(window_ptr_);
        SDL_Delay(16);
    }
    return 0;
}

application::~application()
{
    SDL_FreeSurface(background_);
    //SDL_FreeSurface(window_surface_ptr_);
    SDL_DestroyWindow(window_ptr_);
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

void ground::update() {
    std::for_each(animals.begin(), animals.end(),[](std::shared_ptr<animal> animal) {
        animal->move();
        animal->draw();
    });
}

void ground::add_animal(const std::shared_ptr<animal>& animal)
{
    animals.push_back(animal);
}

animal::animal(const std::string &file_path, SDL_Surface *window_surface_ptr, int animal_height, int animal_width) {
    this->window_surface_ptr_ = window_surface_ptr;
    this->image_ptr_ = load_surface_for(file_path, window_surface_ptr);
    this->_w_size = animal_width;
    this->_h_size = animal_height;

    this->_y = (random() % (frame_height - _h_size));
    this->_x = (random() % (frame_width - _w_size));
    time_to_change = 0;

}

animal::~animal() {
    SDL_FreeSurface(this->image_ptr_);
    this->image_ptr_ = nullptr;
}

void animal::draw() {

    SDL_Rect img_rect{_x, _y, _h_size, _w_size};
    if(SDL_BlitSurface(image_ptr_,NULL,window_surface_ptr_ ,&img_rect)) {
        throw std::runtime_error("cannot draw animal");
    }
}

void animal::get_next_pos() {
    if (time_to_change > SDL_GetTicks()) {
        _x = (_x_dir - _x) < speed ? _x : _x + ((_x_dir < _x ? -1 : 1) * speed);
        _y = (_y_dir - _y) < speed ? _y : _y + ((_y_dir < _y ? -1 : 1) * speed);
        return;
    }

    _y_dir = (random() % (frame_height - _h_size));
    _x_dir = (random() % (frame_width - _w_size));
    
    _x = (_x_dir - _x) < speed ? _x : _x + ((_x_dir < _x ? -1 : 1) * speed);
    _y= (_y_dir - _y) < speed ? _y : _y + ((_y_dir < _y ? -1 : 1) * speed);
    this->time_to_change = SDL_GetTicks() + (random() % 4000);
}


void Sheep::move() {
    get_next_pos();
}

void Wolf::move() {
    get_next_pos();
}

Sheep::Sheep(SDL_Surface *window_surface_ptr): animal(path_img_sheep, window_surface_ptr, 71, 67) {
    speed = 1;
}

Wolf::Wolf(SDL_Surface *window_surface_ptr) : animal(path_img_wolf, window_surface_ptr, 42, 62) {
    speed = 1;
}
