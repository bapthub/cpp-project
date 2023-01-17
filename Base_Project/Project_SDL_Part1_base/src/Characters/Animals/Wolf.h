#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include "Animal.h"
#include <string>

const std::string path_img_wolf = "../../media/wolf.png";
const int wolf_height = 71;
const int wolf_width = 67; 
const int spawn_wolf_life = 5;

class Wolf : public Animal {
private: 
    int distance_nearest_sheep = -1;
    static const int H_AREA_EFFECT = wolf_height * 3;
    static const int W_AREA_EFFECT = wolf_width * 3;
public:
    explicit Wolf(SDL_Surface *window_surface_ptr);

    ~Wolf() override = default;

    void move() override;

    std::shared_ptr<Animal> procreate(Animal &animal) override;

    int collide(Animal& animal, std::vector<std::shared_ptr<Animal>>& animals) override;
    
    int change_direction(int cor_to_change,int cor_to_check);
    int avoid_dog(Animal& animal);
    bool hunt(Animal& animal);
};

