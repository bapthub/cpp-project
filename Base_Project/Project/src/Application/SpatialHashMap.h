#pragma once

#include <unordered_map>
#include <set>
#include <vector>
#include "./Point.h"
#include "../Utils/Utils.h"
#include "../Characters/Animals/Animal.h"

struct PointHash {
    std::size_t operator()(const Point& p) const {
        return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
    }
};

struct PointEqual {
    bool operator()(const Point& p1, const Point& p2) const {
        return p1.x == p2.x && p1.y == p2.y;
    }
};

class SpatialHashMap {
    private:
        std::unordered_map<Point, std::vector<Animal*>, PointHash, PointEqual> buckets_;
        std::set<Point> getBucketsPoints(const Animal& object);
        bool areHitboxesColliding(const Animal& p1, const Animal& p2);
        const static int BUCKET_SIZE = 100;

    public:
        void add(Animal& object);
        void clear();
        void removeObject(Animal& object);
        std::vector<Animal*> checkCollisions(Animal& object);
};
