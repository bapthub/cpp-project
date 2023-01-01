
#ifndef PROJECT_SDL1_POINT_H
#define PROJECT_SDL1_POINT_H

struct Point {
public:
    int x;
    int y;

    bool operator<(const Point& other) const {
        if (x < other.x) {
            return true;
        } else if (x == other.x) {
            return y < other.y;
        } else {
            return false;
        }
    }

};

#endif //PROJECT_SDL1_POINT_H
