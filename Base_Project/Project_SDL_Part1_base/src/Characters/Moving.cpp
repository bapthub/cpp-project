
#include "Moving.h"

Moving::Moving(unsigned int speed) {
    this->speed = speed;
    this->initial_speed = speed;
}

void Moving::buffSpeed(int coef, int duration) {
    if (speed == initial_speed) {
        this->speed = 2;
        this->buff_speed_duration = duration;
    }
}
