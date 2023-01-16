
#include "Dog.h"
#include "../../Application/Application.h"

Dog::Dog(SDL_Surface *window_surface_ptr) : Animal(
       path_img_dog,
       window_surface_ptr,
       dog_height,
       dog_width,
       1,
       ObjectType::DOG
    ){}

void Dog::move() {
    //TODO code dupliqué par rapport à sheep mais il doit changer dans la partie 2
    if (time_to_change > SDL_GetTicks()) {
        point.x= (_x_dir - point.x) < speed ? point.x: point.x+ ((_x_dir < point.x? -1 : 1) * speed);
        point.y= (_y_dir - point.y) < speed ? point.y: point.y+ ((_y_dir < point.y? -1 : 1) * speed);
        return;
    }

    _y_dir = (random() % (frame_height - h_size));
    _x_dir = (random() % (frame_width - w_size));

    point.x= (_x_dir - point.x) < speed ? point.x: point.x+ ((_x_dir < point.x? -1 : 1) * speed);
    point.y = (_y_dir - point.y) < speed ? point.y: point.y+ ((_y_dir < point.y? -1 : 1) * speed);
    this->time_to_change = SDL_GetTicks() + (random() % 4000);
}

std::shared_ptr<Animal> Dog::procreate(Animal &animal) {
    return nullptr;
}

void Dog::collide(Animal& animal, std::vector<std::shared_ptr<Animal>>& animals)
{

}