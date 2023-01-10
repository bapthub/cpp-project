
#include "Sheep.h"
#include "../../Application/Application.h"

Sheep::Sheep(SDL_Surface *window_surface_ptr) : Animal(
        path_img_sheep,
        window_surface_ptr,
        SHEEP_HEIGHT,
        SHEEP_WIDTH,
        1,
        ObjectType::SHEEP
){
    this->gender = random() % 2 ? Gender::FEMALE : Gender::MALE;
    this->setAreaEffect(H_AREA_EFFECT, W_AREA_EFFECT);
}

Sheep::Sheep(SDL_Surface *window_surface_ptr, Point point): Animal(
        path_img_sheep,
        window_surface_ptr,
        SHEEP_HEIGHT,
        SHEEP_WIDTH,
        1,
        ObjectType::SHEEP,
        point
){
    gender = random() % 2 ? Gender::FEMALE : Gender::MALE;
    this->setAreaEffect(H_AREA_EFFECT, W_AREA_EFFECT);
}

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

std::shared_ptr<Animal> Sheep::procreate(Animal &animal)
{
    if (animal.type == ObjectType::SHEEP &&
        (this->gender ^ animal.gender) &&
        this->next_procreate_timestamp < SDL_GetTicks() &&
        animal.next_procreate_timestamp < SDL_GetTicks()
    )
    {
        auto new_animal = std::make_shared<Sheep>(this->window_surface_ptr_, this->point);
        new_animal->next_procreate_timestamp = SDL_GetTicks() + PROCREATE_DELAY;
        if (this->gender == Gender::FEMALE) {
            this->next_procreate_timestamp = SDL_GetTicks() + PROCREATE_DELAY;
        } else {
            animal.next_procreate_timestamp = SDL_GetTicks() + PROCREATE_DELAY;
        }

        return new_animal;
    }

    return nullptr;
}

void Sheep::collide(Animal &animal, std::vector<std::shared_ptr<Animal>> &animals) {

    if (areAdjacent(animal)) {
        auto new_animal = procreate(animal);
        if (new_animal != nullptr) {
            animals.push_back(new_animal);
        }
    }

    if (animal.type == ObjectType::WOLF) {
        buffSpeed(2, SDL_GetTicks() + 10000);
    }
}

