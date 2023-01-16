#pragma once

class Moving {
public:
    explicit Moving(unsigned speed);
    virtual void move() = 0;
    void buffSpeed(int coef, int duration);

protected:
    unsigned _x_dir = 0;
    unsigned _y_dir = 0;
    unsigned speed;
    unsigned initial_speed = 0;
    unsigned buff_speed_duration = 0;
};
