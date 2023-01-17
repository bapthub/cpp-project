
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
    int range = 300;
    bool is_moving = false;
    speed = 30;

    // SDL2 get mouse position
    int mouse_x, mouse_y;

    if (SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SDL_GetMouseState(&mouse_x, &mouse_y);
            is_moving = true;
            _x_dir = mouse_x;
            _y_dir = mouse_y;
        }

    if (!is_moving)
    {
        if (time_to_change > SDL_GetTicks()) 
        {
            point.x= (_x_dir - point.x) < speed ? point.x: point.x+ ((_x_dir < point.x? -1 : 1) * speed);
            point.y= (_y_dir - point.y) < speed ? point.y: point.y+ ((_y_dir < point.y? -1 : 1) * speed);
            return;
        }

        _y_dir = (((rand() % (center_y + range - (center_y - range))) + center_y - range) % (frame_height - h_size));
        _x_dir = (((rand() % (center_x + range - (center_x - range))) + center_x - range) % (frame_width - w_size));

        point.x= (_x_dir - point.x) < speed ? point.x: point.x+ ((_x_dir < point.x? -1 : 1) * speed);
        point.y= (_y_dir - point.y) < speed ? point.y: point.y+ ((_y_dir < point.y? -1 : 1) * speed);
        this->time_to_change = SDL_GetTicks() + (random() % 4000);
    }

    while (is_moving)
    {
        point.x= (_x_dir - point.x) < speed ? point.x: point.x+ ((_x_dir < point.x? -1 : 1) * speed);
        point.y= (_y_dir - point.y) < speed ? point.y: point.y+ ((_y_dir < point.y? -1 : 1) * speed);

        if (point.x == _x_dir && point.y == _y_dir)
        {
            is_moving = false;
        }
    }
}

std::shared_ptr<Animal> Dog::procreate(Animal &animal) 
{
    return nullptr;
}

void Dog::collide(Animal& animal, std::vector<std::shared_ptr<Animal>>& animals)
{

}