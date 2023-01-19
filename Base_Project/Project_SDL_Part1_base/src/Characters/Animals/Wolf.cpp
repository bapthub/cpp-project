
#include "Wolf.h"
#include "Sheep.h"
#include "../../Application/Application.h"

#include <iostream>

Wolf::Wolf(SDL_Surface *window_surface_ptr) : Animal(
       path_img_wolf,
       window_surface_ptr,
       wolf_height,
       wolf_width,
       1,
       ObjectType::WOLF
       
    ){
        this->setAreaEffect(H_AREA_EFFECT, W_AREA_EFFECT);
        this->life = spawn_wolf_life * frame_rate;
        this->distance_nearest_sheep = -1;
    }

void removeFromVector(std::vector<std::shared_ptr<Animal>>& animals, Animal* animal)
{
    auto it = std::find_if(animals.begin(), animals.end(),
                           [animal](const std::shared_ptr<Animal>& a) { return a.get() == animal; });
    if (it != animals.end())
        animals.erase(it);
}

int Wolf::change_direction(int cor_to_change,int cor_to_check)
{
    if (cor_to_change < cor_to_check)
    {
        return cor_to_change - speed;
    }
    return cor_to_change + speed;
}

int Wolf::avoid_dog(Animal& animal)
{
    // std::cout << "avoiding dog" << std::endl;
    if (animal.type == ObjectType::DOG)
    {
        this->_x_dir = change_direction(this->point.x,animal.point.x);
        this->_y_dir = change_direction(this->point.y,animal.point.y);
        return 1;
    }
    return 0;
}

bool Wolf::hunt(Animal& animal)
{
    if (animal.type == ObjectType::SHEEP)
    {
        int distance = std::abs(animal.point.x - this->point.x) + std::abs(animal.point.y - this->point.y);
        if (distance < this->distance_nearest_sheep || this->distance_nearest_sheep == -1)
        {
            this->distance_nearest_sheep = distance;
        }
        this->_x_dir = animal.point.x;
        this->_y_dir = animal.point.y;
        return this->areAdjacent(animal);
    }
    return false;
}

int Wolf::collide(Animal& animal, std::vector<std::shared_ptr<Animal>>& animals)
{
    if (avoid_dog(animal) == 1)
    {
        return 0;
    }

    if (hunt(animal) == 1)
    {
        this->life += 5 * frame_rate; 
        this->distance_nearest_sheep = -1; //reset distance
        removeFromVector(animals,&animal);
        return 1;
    }

    if (animal.type == ObjectType::DOG) {
        buffSpeed(2, SDL_GetTicks() + 10000);
    }

    return 0;
}

void Wolf::move() {
    // TODO code dupliqué par rapport à sheep mais il doit changer dans la partie 2
    if (time_to_change > SDL_GetTicks() && this->distance_nearest_sheep == -1) {
        point.x = (_x_dir - point.x) < speed ? point.x: point.x+ ((_x_dir < point.x? -1 : 1) * speed);
        point.y = (_y_dir - point.y) < speed ? point.y: point.y+ ((_y_dir < point.y? -1 : 1) * speed);
        return;
    }

    if (this->distance_nearest_sheep == -1)
    {
        _y_dir = (random() % (frame_height - h_size));
        _x_dir = (random() % (frame_width - w_size));
    }
    
    point.x = (_x_dir - point.x) < speed ? point.x: point.x+ ((_x_dir < point.x? -1 : 1) * speed);
    point.y = (_y_dir - point.y) < speed ? point.y: point.y+ ((_y_dir < point.y? -1 : 1) * speed);
    this->time_to_change = SDL_GetTicks() + (random() % 4000);
}

std::shared_ptr<Animal> Wolf::procreate(Animal &animal) {
    return nullptr;
}

