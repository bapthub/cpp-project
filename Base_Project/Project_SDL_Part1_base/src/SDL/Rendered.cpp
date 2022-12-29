
#include "Rendered.h"

Rendered::Rendered(
        int x,
        int y,
        int h_size,
        int w_size,
        const std::string& file_path,
        SDL_Surface* window_surface_ptr
) {
    this->_x = x;
    this->_y = y;
    this->_h_size = h_size;
    this->_w_size = w_size;
    this->window_surface_ptr_ = window_surface_ptr;
    this->image_ptr_ = load_surface_for(file_path, window_surface_ptr);
}

Rendered::~Rendered() {
    SDL_FreeSurface(this->image_ptr_);
    this->image_ptr_ = nullptr;
}

SDL_Surface* Rendered::load_surface_for(const std::string& path, SDL_Surface* window_surface_ptr) {

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
}

void Rendered::draw() {
    SDL_Rect img_rect{_x, _y, _h_size, _w_size};
    if(SDL_BlitSurface(image_ptr_,NULL,window_surface_ptr_ ,&img_rect)) {
        throw std::runtime_error("cannot draw animal");
    }
}