#pragma once

class Moving {
public:
    explicit Moving(unsigned speed);
    virtual void move() = 0;

protected:
    unsigned _x_dir = 0;
    unsigned _y_dir = 0;
    unsigned speed;
};
