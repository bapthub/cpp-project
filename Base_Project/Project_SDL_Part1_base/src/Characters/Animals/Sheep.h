#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include "Animal.h"
#include <string>

const std::string path_img_sheep = "../../media/sheep.png";

class Sheep : public Animal {
public:
    static const int PROCREATE_DELAY = 10000;

    static const int SHEEP_HEIGHT = 42;
    static const int SHEEP_WIDTH = 62;

    static const int H_AREA_EFFECT = SHEEP_HEIGHT * 3;
    static const int W_AREA_EFFECT = SHEEP_WIDTH * 3;

    explicit Sheep(SDL_Surface *window_surface_ptr);

    Sheep(SDL_Surface *window_surface_ptr, Point point);

    ~Sheep() override = default;

    void move() override;

    std::shared_ptr<Animal> procreate(Animal &animal) override;

    void collide(Animal& animal, std::vector<std::shared_ptr<Animal>>& animals) override;

};
