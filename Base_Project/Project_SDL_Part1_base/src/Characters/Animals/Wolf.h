#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include <string>
#include <iostream>
#include "Animal.h"
#include "../../Application/Application.h"

const std::string path_img_wolf = "../../media/wolf.png";
const int wolf_height = 71;
const int wolf_width = 67; 
const int spawn_wolf_life = 5;

class Wolf : public Animal {
private: 
    int distance_nearest_sheep = -1;
    static const int H_AREA_EFFECT = wolf_height * 4;
    static const int W_AREA_EFFECT = wolf_width * 4;
public:
    explicit Wolf(SDL_Surface *window_surface_ptr);

    ~Wolf() override = default;

    void move() override;

    std::shared_ptr<Animal> procreate(Animal &animal) override;

    void collide(Animal& animal, std::vector<std::shared_ptr<Animal>>& animals) override;
    
    int avoid_dog(Animal& animal);
    bool hunt(Animal& animal);
};

