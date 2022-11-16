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

} // namespace

application::application(unsigned n_sheep, unsigned n_wolf)
{
    window_ptr_ = create_window();
    if (window_ptr_ == nullptr) {
        throw std::runtime_error("application(): " + std::string(SDL_GetError()));
    }

    window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);

    SDL_Surface *image = IMG_Load(path_img_grass);
    SDL_Surface* formatted_image = SDL_ConvertSurface(image, window_surface_ptr_->format, 0);
    if (formatted_image == NULL) {
        throw std::runtime_error("can't format surface");
    }

    SDL_FreeSurface(image);

    int return_val = SDL_BlitSurface(formatted_image,NULL,window_surface_ptr_ ,NULL);

    std::cout << "return_val: " << return_val << std::endl;

    ground_ = new ground(window_surface_ptr_, n_sheep, n_wolf);

    SDL_UpdateWindowSurface(window_ptr_);
}

int application::loop(unsigned window_time)
{
    while(SDL_GetTicks() < window_time * 1000) {
        ground_->update();
        SDL_UpdateWindowSurface(window_ptr_);
    }
    return 0;
}

application::~application()
{
    SDL_FreeSurface(window_surface_ptr_);
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

void ground::update() {
    std::for_each(animals.begin(), animals.end(),[](std::shared_ptr<animal> animal) {
        animal->move();
    });
}

void ground::add_animal(const std::shared_ptr<animal>& animal)
{
    animals.push_back(animal);
}

animal::animal(const std::string &file_path, SDL_Surface *window_surface_ptr) {
    this->window_surface_ptr_ = window_surface_ptr;
    this->image_ptr_ = load_surface_for(file_path, window_surface_ptr);

    this->_y = random() % window_surface_ptr->h;
    this->_x = random() % window_surface_ptr->w;

    if (this->_y < _h_size) {
        this->_y =+_h_size;
    }
    if (this->_y > window_surface_ptr->h - _h_size) {
        this->_y =- _h_size;
    }

    if (this->_x < _w_size) {
        this->_x =- _w_size;
    }
    if (this->_x < window_surface_ptr->w - _w_size) {
        this->_x =+ _w_size;
    }

    std::cout<<this->_y<< std::endl;
    std::cout<<this->_x<< std::endl;


    this->time_to_change = SDL_GetTicks() + (random() % 4000);
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
        _x = _x_dir - _x < speed ? 0 : _x + ((_x_dir < _x ? -1 : 1) * speed);
        _y = _y_dir - _y < speed ? 0 : _y + ((_y_dir < _y ? -1 : 1) * speed);
        return;
    }

    _y_dir = (random() % (window_surface_ptr_->h - _h_size)) + _h_size / 2;
    _x_dir = (random() % (window_surface_ptr_->w - _w_size)) + _w_size / 2;

    _x = _x_dir - _x < speed ? 0 : _x + ((_x_dir < _x ? -1 : 1) * speed);
    _y= _y_dir - _y < speed ? 0 : _y + ((_y_dir < _y ? -1 : 1) * speed);
}


void Sheep::move() {
    get_next_pos();
}

void Wolf::move() {
    get_next_pos();
}

Sheep::Sheep(SDL_Surface *window_surface_ptr): animal(path_img_sheep, window_surface_ptr) {
    this->_h_size = 71;
    this->_w_size = 67;
}

Wolf::Wolf(SDL_Surface *window_surface_ptr) : animal(path_img_wolf, window_surface_ptr) {
    this->_h_size = 42;
    this->_w_size = 62;
}
