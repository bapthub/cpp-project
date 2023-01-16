
#ifndef PROJECT_SDL1_COLLIDE_H
#define PROJECT_SDL1_COLLIDE_H

#include <vector>
#include "../Utils/Utils.h"

#include "../SDL/Rendered.h"
#include "../Characters/Animals/Sheep.h"
#include "../Characters/Animals/Wolf.h"

class Collide {
    public:
        static void collide(
                Animal& animal1,
                Animal& animal2,
                std::vector<std::shared_ptr<Animal>>& animals
                );
};


#endif
