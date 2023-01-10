#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include "Animal.h"
#include <string>

const std::string path_img_wolf = "./media/wolf.png";
const int wolf_height = 71;
const int wolf_width = 67; 
const int spawn_wolf_life = 5;

class Wolf : public Animal {
private: 
    int life = 5;
    int distance_nearest_sheep = -1;
public:
    explicit Wolf(SDL_Surface *window_surface_ptr);

    ~Wolf() override = default;

    void move() override;

    std::shared_ptr<Animal> procreate(Animal &animal) override;

    void collide(Animal& animal, std::vector<std::shared_ptr<Animal>>& animals) override;
    
    int change_direction(int cor_to_change,int cor_to_check,int direction);
    int avoid_dog(Wolf& wolf,std::vector<std::shared_ptr<Animal>>& animals);
    bool hunt(Wolf& wolf,std::vector<std::shared_ptr<Animal>>& animals);
};

