
#include "Animal.h"
#include "../../Application/Application.h"


Animal::Animal(
        const std::string &file_path,
        SDL_Surface *window_surface_ptr,
        int animal_height,
        int animal_width,
        unsigned speed
        ) {
    this->window_surface_ptr_ = window_surface_ptr;
    this->image_ptr_ = Application::load_surface_for(file_path, window_surface_ptr);
    this->_w_size = animal_width;
    this->_h_size = animal_height;
    this->speed = speed;
    this->_y = (random() % (frame_height - _h_size));
    this->_x = (random() % (frame_width - _w_size));
    time_to_change = 0;

}

Animal::~Animal() {
    SDL_FreeSurface(this->image_ptr_);
    this->image_ptr_ = nullptr;
}

void Animal::draw() {

    SDL_Rect img_rect{_x, _y, _h_size, _w_size};
    if(SDL_BlitSurface(image_ptr_,NULL,window_surface_ptr_ ,&img_rect)) {
        throw std::runtime_error("cannot draw animal");
    }
}

void Animal::get_next_pos() {
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