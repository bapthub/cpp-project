
#include "Moving.h"

Moving::Moving(unsigned int speed) {
    this->speed = speed;
    this->initial_speed = speed;
}

void Moving::buffSpeed(int coef, int duration) {
    this->speed = speed *coef;
    this->buff_speed_duration = duration;
}
