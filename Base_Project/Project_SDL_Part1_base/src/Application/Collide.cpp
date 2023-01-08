

#include "Collide.h"
#include <iostream>

void Collide::collide(
        const Rendered& object,
        const Animal& animal,
        std::vector<std::shared_ptr<Animal>>& animals,
        SDL_Surface* window_surface_ptr
){
    auto sheep_o = dynamic_cast<const Sheep*>(&object);
    auto sheep_a = dynamic_cast<const Sheep*>(&animal);
    auto wolf_o = dynamic_cast<const Wolf*>(&object);
    auto wolf_a = dynamic_cast<const Wolf*>(&animal);

    if (sheep_a != nullptr && sheep_o) {
//        if (sheep_o.gender ^ sheep_a.gender) {
//            animals.push_back(std::make_shared<Sheep>(window_surface_ptr, sheep_o->point));
//        }
    }

    if (wolf_o && wolf_a) {

    }

}
