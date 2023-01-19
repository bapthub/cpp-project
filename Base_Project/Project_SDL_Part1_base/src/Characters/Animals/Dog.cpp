#include "Dog.h"
#include "../../Application/Application.h"

Dog::Dog(SDL_Surface *window_surface_ptr) : Animal(
        path_img_dog,
        window_surface_ptr,
        dog_height,
        dog_width,
        1,
        ObjectType::DOG,
        Point{0, 0}
){}

int click_target_x = -1;        // The target of the dog
int click_target_y = -1;

int shepherd_x = -1;            // The position of the shepherd
int shepherd_y = -1;

bool is_moving = false;         // If the dog is moving towards a target

int range = 200;                // Area around the center where the dog can move

void Dog::move()
{
    speed = 3;

    std::pair<int, int> shepherd_position = get_shepherd_position();
    int center_x = shepherd_position.first;
    int center_y = shepherd_position.second;

    std::pair<int, int> dog_target = get_dog_target();

    // If a position is clicked, is_moving is set to true and the dog moves to the clicked position
    // The target position is set to the clicked position
    if (dog_target.first != -1)
    {
        _x_dir = (dog_target.first - dog_width / 2) % (frame_height - h_size);
        _y_dir = (dog_target.second - dog_height / 2) % (frame_height - h_size);
        set_dog_target(-1, -1);
        is_moving = true;
    }

    if (point.x == _x_dir && point.y == _y_dir && is_moving)
    {
        std::cout << "Dog reached target" << std::endl;
        is_moving = false;
    }

    // Else random movement around the shepherd

    if (time_to_change > SDL_GetTicks())
    {
        point.x= (_x_dir - point.x) < speed ? point.x: point.x+ ((_x_dir < point.x? -1 : 1) * speed);
        point.y= (_y_dir - point.y) < speed ? point.y: point.y+ ((_y_dir < point.y? -1 : 1) * speed);
        return;
    }

    if ((time_to_change < SDL_GetTicks()) && !is_moving)
    {
        int min_y = (center_y - range);
        if (min_y < 0)
            min_y = 0;
        int max_y = (center_y + range);
        if (max_y > frame_height - h_size)
            max_y = frame_height - h_size;

        int min_x = (center_x - range);
        if (min_x < 0)
            min_x = 0;
        int max_x = (center_x + range);
        if (max_x > frame_width - w_size)
            max_x = frame_width - w_size;

        _y_dir = (min_y + (rand() % (max_y - min_y))) % (frame_height - h_size);
        _x_dir = (min_x + (rand() % (max_x - min_x))) % (frame_width - w_size);
        if (_y_dir < 0)
            _y_dir = dog_height;
        if (_x_dir < 0)
            _x_dir = dog_width;
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

void Dog::collide(Animal& animal, std::vector<std::shared_ptr<Animal>>& animals) {}