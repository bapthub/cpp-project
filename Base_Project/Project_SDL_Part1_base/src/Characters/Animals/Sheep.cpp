
#include "Sheep.h"
#include "../../Application/Application.h"

Sheep::Sheep(SDL_Surface *window_surface_ptr) : Animal(
        path_img_sheep,
        window_surface_ptr,
        sheep_height,
        sheep_width,
        1
){}

Sheep::Sheep(SDL_Surface *window_surface_ptr, Point point): Animal(
        path_img_sheep,
        window_surface_ptr,
        sheep_height,
        sheep_width,
        1,
        point
){}

void Sheep::move() {
    if (time_to_change > SDL_GetTicks()) {
        point.x = (_x_dir - point.x) < speed ? point.x: point.x+ ((_x_dir < point.x? -1 : 1) * speed);
        point.y= (_y_dir - point.y) < speed ? point.y: point.y+ ((_y_dir < point.y? -1 : 1) * speed);
        return;
    }

    _y_dir = (random() % (frame_height - h_size));
    _x_dir = (random() % (frame_width - w_size));

    point.x= (_x_dir - point.x) < speed ? point.x: point.x+ ((_x_dir < point.x? -1 : 1) * speed);
    point.y= (_y_dir - point.y) < speed ? point.y: point.y+ ((_y_dir < point.y? -1 : 1) * speed);
    this->time_to_change = SDL_GetTicks() + (random() % 4000);
}

