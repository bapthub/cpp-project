#pragma once

#include "../Moving.h"
#include "../../SDL/Rendered.h"

enum Gender {
    MALE = 1,
    FEMALE = 2,
    UNKNOWN
};

class Animal: public Moving, public Rendered {
private:
public:
    Animal(
            const std::string& file_path,
            SDL_Surface* window_surface_ptr,
            int animal_height,
            int animal_width,
            unsigned speed,
            ObjectType objectType
            );

    Animal(
            const std::string& file_path,
            SDL_Surface* window_surface_ptr,
            int animal_height,
            int animal_width,
            unsigned speed,
            ObjectType objectType,
            Point point
            );

    Gender gender = Gender::UNKNOWN;

    int next_procreate_timestamp = 0;

    ObjectType type;

    virtual std::shared_ptr<Animal> procreate(Animal& animal) = 0;

protected:
    unsigned time_to_change = 0;
};
