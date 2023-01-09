#ifndef PROJECT_SDL1_UTILS_H
#define PROJECT_SDL1_UTILS_H

#include <vector>
#include "../Characters/Animals/Animal.h"

class Utils {
public:
    template <typename T>
    static void removeFromVector(std::vector<T>& vec, const T& elem) {
        auto it = std::find(vec.begin(), vec.end(), elem);
        if (it != vec.end()) {
            vec.erase(it);
        }
    }

    static bool areAdjacent(Animal& animal1, Animal& animal2);
};


#endif
