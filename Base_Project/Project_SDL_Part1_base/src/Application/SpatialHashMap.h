#ifndef PROJECT_SDL1_SPATIALHASHMAP_H
#define PROJECT_SDL1_SPATIALHASHMAP_H

#include <unordered_map>
#include <set>
#include <vector>
#include "../SDL/Rendered.h"
#include "./Point.h"

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
        std::unordered_map<Point, std::vector<std::shared_ptr<Rendered>>, PointHash, PointEqual> buckets_;
        std::set<Point> getBucketsPoints(std::shared_ptr<Rendered> object);
        bool areHitboxesColliding(const Rendered& p1, const Rendered& p2);
        const int BUCKET_SIZE = 100;

    public:
        void add(std::shared_ptr<Rendered> object);
        std::vector<std::shared_ptr<Rendered>> checkCollisions(std::shared_ptr<Rendered> object);
};

#endif
