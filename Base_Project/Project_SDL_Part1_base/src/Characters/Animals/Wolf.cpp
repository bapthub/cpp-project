#include "Wolf.h"

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

int Wolf::avoid_dog(Animal& animal)
{
    if (animal.type == ObjectType::DOG)
    {
        // Set the direction of the wolf at the opposite of the dog
        auto x_dir = 2 * point.x  + (point.x > animal.point.x ? animal.point.x : - animal.point.x);
        auto y_dir = 2 * point.y  + (point.y > animal.point.y ? animal.point.y : - animal.point.y);
        this->_x_dir = std::min(window_surface_ptr_->w, x_dir > 0 ? x_dir : 0);
        this->_y_dir = std::min(window_surface_ptr_->h, y_dir > 0 ? y_dir : 0);
        return 1;
    }
    return 0;
}

bool Wolf::hunt(Animal& animal)
{
    if (animal.type == ObjectType::SHEEP)
    {
        int distance = std::sqrt(std::abs(animal.point.x - this->point.x)^2 + std::abs(animal.point.y - this->point.y)^2);
        if (distance < this->distance_nearest_sheep || this->distance_nearest_sheep == -1)
        {
            this->distance_nearest_sheep = distance;
            this->_x_dir = animal.point.x;
            this->_y_dir = animal.point.y;
        }
        auto eat = this->areAdjacent(animal);
        // reset the distance
        if (eat) {
            this->distance_nearest_sheep = -1;
        }
        return eat;
    }
    return false;
}

void Wolf::collide(Animal& animal, std::vector<std::shared_ptr<Animal>>& animals)
{
    if (avoid_dog(animal) == 1)
    {
        return;
    }

    if (hunt(animal) == 1)
    {
        this->life += 5 * frame_rate; 
        this->distance_nearest_sheep = -1; //reset distance
        removeFromVector(animals,&animal);
        this->life += 5 * 60;
    }

    if (animal.type == ObjectType::DOG) {
    }
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

