
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

void Wolf::move() {
    // Find the nearest sheep
    Sheep* nearest_sheep = nullptr;
    int min_distance = std::numeric_limits<int>::max();
    for (const auto& animal : Application::get_ground()->animals_) {
        if (auto sheep = dynamic_cast<Sheep*>(animal.get())) {
            // Calculate the distance to the sheep
            int distance = std::abs(sheep->get_x() - _x) + std::abs(sheep->get_y() - _y);
            if (distance < min_distance) {
                min_distance = distance;
                nearest_sheep = sheep;
            }
        }
    }

    // If a sheep was found, move towards it
    if (nearest_sheep) {
        _x_dir = nearest_sheep->get_x();
        _y_dir = nearest_sheep->get_y();
    }
    // Otherwise, choose a new random destination
    else {
        _y_dir = (random() % (frame_height - _h_size));
        _x_dir = (random() % (frame_width - _w_size));
    }

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
}


// void Wolf::move() {
//     //TODO code dupliqué par rapport à sheep mais il doit changer dans la partie 2
//     // if (time_to_change > SDL_GetTicks()) {
//     //     _x = (_x_dir - _x) < speed ? _x : _x + ((_x_dir < _x ? -1 : 1) * speed);
//     //     _y = (_y_dir - _y) < speed ? _y : _y + ((_y_dir < _y ? -1 : 1) * speed);
//     //     return;
//     // }

//     // _y_dir = (random() % (frame_height - _h_size));
//     // _x_dir = (random() % (frame_width - _w_size));

//     // _x = (_x_dir - _x) < speed ? _x : _x + ((_x_dir < _x ? -1 : 1) * speed);
//     // _y= (_y_dir - _y) < speed ? _y : _y + ((_y_dir < _y ? -1 : 1) * speed);
//     // this->time_to_change = SDL_GetTicks() + (random() % 4000);
    
// }

void Wolf::hunt()
{
    //TODO
}

void Wolf::avoid_dog()
{
    //TODO
}

void Wolf::update_life()
{
    //TODO
}

std::shared_ptr<Animal> Wolf::procreate(Animal &animal) {
    return nullptr;
}

void Wolf::collide(Animal& animal, std::vector<std::shared_ptr<Animal>>& animals)
{

}
