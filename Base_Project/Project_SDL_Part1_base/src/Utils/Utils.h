#ifndef PROJECT_SDL1_UTILS_H
#define PROJECT_SDL1_UTILS_H

#include <vector>
#include <algorithm>
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
};


#endif
