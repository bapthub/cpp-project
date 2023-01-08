

#include "Collide.h"
#include <iostream>

void Collide::collide(
        Animal& animal1,
        Animal& animal2,
        std::vector<std::shared_ptr<Animal>>& animals
){
    auto new_animal = animal1.procreate(animal2);
    if (new_animal != nullptr) {
        animals.push_back(new_animal);
    }
}
