#include "Sheperd.h"
#include "../../Application/Application.h"

Sheperd::Sheperd(SDL_Surface *window_surface_ptr) : Animal(
       path_img_sheperd,
       window_surface_ptr,
       sheperd_height,
       sheperd_width,
       1
    ){}

void Sheperd::move() {

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