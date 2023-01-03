

#include "Collide.h"
#include <iostream>

void Collide::collide(
        std::shared_ptr<Rendered> object,
        std::shared_ptr<Animal> animal,
        std::vector<std::shared_ptr<Animal>>& animals
){
    if (std::dynamic_pointer_cast<Sheep>(object) && std::dynamic_pointer_cast<Sheep>(animal)) {
        Utils::removeFromVector(animals, std::dynamic_pointer_cast<Animal>(object));
    }

    if (std::dynamic_pointer_cast<Wolf>(object) && std::dynamic_pointer_cast<Wolf>(animal)) {

    }

}
