
#include "Wolf.h"
#include "Sheep.h"
#include "../../Application/Application.h"

#include <iostream>

Wolf::Wolf(SDL_Surface *window_surface_ptr) : Animal(
       path_img_wolf,
       window_surface_ptr,
       wolf_height,
       wolf_width,
       3,
       spawn_wolf_life * frame_rate,
       ObjectType::WOLF
       
    ){
        this->setAreaEffect(H_AREA_EFFECT, W_AREA_EFFECT);
        this->life = spawn_wolf_life * frame_rate;
    }

void removeFromVector(std::vector<std::shared_ptr<Animal>>& animals, Animal* animal)
{
    auto it = std::find_if(animals.begin(), animals.end(),
                           [animal](const std::shared_ptr<Animal>& a) { return a.get() == animal; });
    if (it != animals.end())
        animals.erase(it);
}

//with direction = -1 you go away, with direction = 1 you get closer
int Wolf::change_direction(int cor_to_change,int cor_to_check,int direction)
{
    if (direction == -1)
    {
        if (cor_to_change < cor_to_check)
        {
            return cor_to_change - (1 * speed);
        }
        return cor_to_change + (1 * speed);
    }
    else
    {
        if (cor_to_change < cor_to_check)
        {
            return cor_to_change + (1 * speed);
        }
        return cor_to_change - (1 * speed);
    }
}

void Wolf::avoid_dog(Animal& animal)
{
    // std::cout << "avoiding dog" << std::endl;
    if (animal.type == ObjectType::DOG)
    {
        this->point.x = change_direction(this->point.x,animal.point.x,-1);
        this->point.y = change_direction(this->point.y,animal.point.y,-1);
    }
}

bool Wolf::hunt(Animal& animal)
{
    // std::cout << animal.type << std::endl;
    if (animal.type == ObjectType::SHEEP)
    {
        int distance = std::abs(animal.point.x - this->point.x) + std::abs(animal.point.y - this->point.y);
        if (distance < this->distance_nearest_sheep)
        {
            this->distance_nearest_sheep = distance;
        }
        // std::cout << "old x :" << this->point.x << std::endl;
        // std::cout << "old y :" << this->point.y << std::endl;
        this->point.x = change_direction(this->point.x,animal.point.x,1);
        this->point.y = change_direction(this->point.y,animal.point.y,1);
        // std::cout << "new x :" << this->point.x << std::endl;
        // std::cout << "new y :" << this->point.y << std::endl;
        return this->areAdjacent(animal);
    }
    return false;
}

int Wolf::collide(Animal& animal, std::vector<std::shared_ptr<Animal>>& animals)
{
    // std::cout << "collide" << std::endl;
    avoid_dog(animal);
    if (hunt(animal) == 1)
    {
        // std::cout << this->life << std::endl;
        // this->life = spawn_wolf_life;
        // std::cout << this->life << std::endl;
        removeFromVector(animals,&animal);
        std::cout << "remove sheep" << std::endl;
        return 1;
    }
    return 0;
}

void Wolf::move() {
    // TODO code dupliqué par rapport à sheep mais il doit changer dans la partie 2
    if (time_to_change > SDL_GetTicks()) {
        point.x = (_x_dir - point.x) < speed ? point.x: point.x+ ((_x_dir < point.x? -1 : 1) * speed);
        point.y = (_y_dir - point.y) < speed ? point.y: point.y+ ((_y_dir < point.y? -1 : 1) * speed);
        return;
    }

    _y_dir = (random() % (frame_height - h_size));
    _x_dir = (random() % (frame_width - w_size));

    point.x = (_x_dir - point.x) < speed ? point.x: point.x+ ((_x_dir < point.x? -1 : 1) * speed);
    point.y = (_y_dir - point.y) < speed ? point.y: point.y+ ((_y_dir < point.y? -1 : 1) * speed);
    this->time_to_change = SDL_GetTicks() + (random() % 4000);
}

std::shared_ptr<Animal> Wolf::procreate(Animal &animal) {
    return nullptr;
}

