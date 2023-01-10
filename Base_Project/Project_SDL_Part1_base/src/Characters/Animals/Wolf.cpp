
#include "Wolf.h"
#include "Sheep.h"
#include "../../Application/Application.h"

Wolf::Wolf(SDL_Surface *window_surface_ptr) : Animal(
       path_img_wolf,
       window_surface_ptr,
       wolf_height,
       wolf_width,
       1,
       ObjectType::WOLF
    ){}

//with direction = -1 you go away, with direction = 1 you get closer
int Wolf::change_direction(int cor_to_change,int cor_to_check,int direction)
{
    if (direction == -1)
    {
        if (cor_to_change < cor_to_check)
        {
            return cor_to_change - 1;
        }
        return cor_to_change + 1;
    }
    else
    {
        if (cor_to_change < cor_to_check)
        {
            return cor_to_change + 1;
        }
        return cor_to_change - 1;
    }
}

int Wolf::avoid_dog(Wolf& wolf,std::vector<std::shared_ptr<Animal>>& animals)
{
    for (auto animal : animals)
    {
        if (animal->type == ObjectType::DOG)
        {
            wolf.point.x = change_direction(wolf.point.x,animal->point.x,-1);
            wolf.point.y = change_direction(wolf.point.y,animal->point.y,-1);
            return 0;
        }
    }
    return -1;
}

bool Wolf::hunt(Wolf& wolf,std::vector<std::shared_ptr<Animal>>& animals)
{
    int distance_nearest_sheep = 10000;
    Animal *nearest_sheep = nullptr;
    // for (auto animal = animals.begin(); animal != animals.end(); ++animal)
    // std::for_each(animals.begin(), animals.end(),[this](const std::shared_ptr<Animal>& animal) 
    for (auto animal : animals)
    {
        if (animal->type == ObjectType::SHEEP)
        {
            int distance = std::abs(animal->point.x - wolf.point.x) + std::abs(animal->point.y - wolf.point.y);
            if (distance < distance_nearest_sheep)
            {
                distance_nearest_sheep = distance;
                nearest_sheep = animal;
            }
        }
    }
    if(!nearest_sheep)
    { 
        return false;
    }

    wolf.point.x = change_direction(wolf.point.x,nearest_sheep->point.x,1);
    wolf.point.y = change_direction(wolf.point.y,nearest_sheep->point.y,1);
    return wolf.areAdjacent(nearest_sheep);
}

void Wolf::collide(Animal& wolf, std::vector<std::shared_ptr<Animal>>& animals)
{
    if (avoid_dog(wolf,animals) == 0)
    {
        wolf.life -= 1;
        return;
    }
    if (hunt(wolf,animals) == 1)
    {
        wolf.life = spawn_wolf_life;
        return;
    }
    else
    {
        wolf.life -= 1;
    }
}

void Wolf::move() {
    // TODO code dupliqué par rapport à sheep mais il doit changer dans la partie 2
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

// void Wolf::move() {
//     // Find the nearest sheep
//     Sheep* nearest_sheep = nullptr;
//     int min_distance = std::numeric_limits<int>::max();
//     for (const auto& animal : Application::get_ground()->animals_) {
//         if (auto sheep = dynamic_cast<Sheep*>(animal.get())) {
//             // Calculate the distance to the sheep
//             int distance = std::abs(sheep->get_x() - _x) + std::abs(sheep->get_y() - _y);
//             if (distance < min_distance) {
//                 min_distance = distance;
//                 nearest_sheep = sheep;
//             }
//         }
//     }

//     // If a sheep was found, move towards it
//     if (nearest_sheep) {
//         _x_dir = nearest_sheep->get_x();
//         _y_dir = nearest_sheep->get_y();
//     }
//     // Otherwise, choose a new random destination
//     else {
//         _y_dir = (random() % (frame_height - _h_size));
//         _x_dir = (random() % (frame_width - _w_size));
//     }

    // Check if the sheepdog is close to the wolf
    // bool sheepdog_nearby = false;
    // for (const auto& animal : Application::get_ground()->animals_) {
    //     if (auto sheepdog = dynamic_cast<Sheepdog*>(animal.get())) {
    //         int distance = std::abs(sheepdog->get_x() - _x) + std::abs(sheepdog->get_y() - _y);
    //         if (distance < sheepdog_fear_radius) {
    //             sheepdog_nearby = true;
    //             break;
    //         }
    //     }
    // }

    // If the sheepdog is nearby, choose a new random destination away from it
    // if (sheepdog_nearby) {
    //     int max_distance = 0;
    //     for (int y = 0; y < frame_height - _h_size; ++y) {
    //         for (int x = 0; x < frame_width - _w_size; ++x) {
    //             int distance = std::abs(x - _x) + std::abs(y - _y);
    //             bool sheepdog_too_close = false;
    //             for (const auto& animal : Application::get_ground()->animals_) {
    //                 if (auto sheepdog = dynamic_cast<Sheepdog*>(animal.get())) {
    //                     int sheepdog_distance = std::abs(sheepdog->get_x() - x) + std::abs(sheepdog->get_y() - y);
    //                     if (sheepdog_distance < sheepdog_fear_radius) {
    //                         sheepdog_too_close = true;
    //                         break;
    //                     }
    //                 }
    //             }
    //             if (!sheepdog_too_close && distance > max_distance) {
    //                 _x_dir = x;
    //                 _y_dir = y;
    //                 max_distance = distance;
    //             }
            // }
// }

std::shared_ptr<Animal> Wolf::procreate(Animal &animal) {
    return nullptr;
}

