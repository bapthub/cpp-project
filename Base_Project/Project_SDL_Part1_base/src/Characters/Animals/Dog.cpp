
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

void Dog::move() 
{
    // Initialize the character's position and movement variables

    // _x_dir : Target x position, must be in the visible area and in the range around the center
    // _y_dir : Target y position, must be in the visible area and in the range around the center
    // point.x : Current x position
    // point.y : Current y position
    // speed : Speed of the character

    int center_x = 300;
    int center_y = 300;
    int range = 100;
    speed = 20;

    if (time_to_change > SDL_GetTicks()) {
        point.x = (_x_dir - point.x) < speed ? point.x: point.x+ ((_x_dir < point.x? -1 : 1) * speed);
        point.y= (_y_dir - point.y) < speed ? point.y: point.y+ ((_y_dir < point.y? -1 : 1) * speed);
        return;
    }
int randomNumber = (rand() % (center_y + range - (center_y - range))) + center_y - range;

    _y_dir = (((rand() % (center_y + range - (center_y - range))) + center_y - range) % (frame_height - h_size));
    _x_dir = (((rand() % (center_x + range - (center_x - range))) + center_x - range) % (frame_width - w_size));

    point.x= (_x_dir - point.x) < speed ? point.x: point.x+ ((_x_dir < point.x? -1 : 1) * speed);
    point.y= (_y_dir - point.y) < speed ? point.y: point.y+ ((_y_dir < point.y? -1 : 1) * speed);
    this->time_to_change = SDL_GetTicks() + (random() % 4000);
}

std::shared_ptr<Animal> Dog::procreate(Animal &animal) 
{
    return nullptr;
}

void Dog::collide(Animal& animal, std::vector<std::shared_ptr<Animal>>& animals)
{

}