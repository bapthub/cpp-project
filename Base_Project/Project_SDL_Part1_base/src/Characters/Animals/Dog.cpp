#include "Dog.h"
#include "../../Application/Application.h"
#include "../../Application/Ground.h"

Dog::Dog(SDL_Surface *window_surface_ptr) : Animal(
       path_img_dog,
       window_surface_ptr,
       dog_height,
       dog_width,
       1,
       ObjectType::DOG,
       Point{0, 0}
    ){}

int click_target_x = -1;                  // The target of the dog
int click_target_y = -1;

int shepherd_x = -1;                      // The position of the shepherd
int shepherd_y = -1;

bool is_moving = false;                   // Is the dog moving to a clicked position


void Dog::move()
{
    // Initialize the character's position and movement variables

    // _x_dir : Target x position, must be in the visible area and in the range around the center
    // _y_dir : Target y position, must be in the visible area and in the range around the center
    // point.x : Current x position
    // point.y : Current y position
    // speed : Speed of the character

    // Area around the center where the dog can move
    int range = 100;
    speed = 4;

    std::pair<int, int> shepherd_position = get_shepherd_position();
    int center_x = shepherd_position.first;
    int center_y = shepherd_position.second;

    std::pair<int, int> dog_target = get_dog_target();
    int click_x = dog_target.first;
    int click_y = dog_target.second;

    // If a position is clicked, is_moving is set to true and the dog moves to the clicked position
    if (click_x != -1 && click_y != -1)
    {
        is_moving = true;
    }

    // If the dog is moving, the target position is set to the clicked position
    if (is_moving)
    {
        _x_dir = click_x;
        _y_dir = click_y;
    }

    // If the dog is at the clicked position, is_moving is set to false
    if (is_moving && point.x == _x_dir && point.y == _y_dir)
    {
        click_x = -1;
        click_y = -1;
        is_moving = false;
    }

    // Else random movement around the shepherd

    else if (time_to_change > SDL_GetTicks() && !is_moving) 
    {
        point.x= (_x_dir - point.x) < speed ? point.x: point.x+ ((_x_dir < point.x? -1 : 1) * speed);
        point.y= (_y_dir - point.y) < speed ? point.y: point.y+ ((_y_dir < point.y? -1 : 1) * speed);
        return;
    }

    else if (!is_moving && (time_to_change < SDL_GetTicks()))
    {
        _y_dir = (((rand() % (center_y + range - (center_y - range))) + center_y - range) % (frame_height - h_size));
        _x_dir = (((rand() % (center_x + range - (center_x - range))) + center_x - range) % (frame_width - w_size));
    }
    
    this->time_to_change = SDL_GetTicks() + (random() % 4000);
}

// Getters and setters

std::pair<int, int> Dog::get_shepherd_position()
{
    return std::make_pair(shepherd_x, shepherd_y);
}

void Dog::set_shepherd_position(int x, int y)
{
    shepherd_x = x;
    shepherd_y = y;
}

std::pair<int, int> Dog::get_dog_target()
{
    return std::make_pair(click_target_x, click_target_y);
}

void Dog::set_dog_target(int x, int y)
{
    click_target_x = x;
    click_target_y = y;
}

std::shared_ptr<Animal> Dog::procreate(Animal &animal) 
{
    return nullptr;
}

void Dog::collide(Animal& animal, std::vector<std::shared_ptr<Animal>>& animals)
{

}