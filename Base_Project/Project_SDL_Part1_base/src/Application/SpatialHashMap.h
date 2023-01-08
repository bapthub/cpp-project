#ifndef PROJECT_SDL1_SPATIALHASHMAP_H
#define PROJECT_SDL1_SPATIALHASHMAP_H

#include <unordered_map>
#include <set>
#include <vector>
#include "../SDL/Rendered.h"
#include "./Point.h"
#include "../Utils/Utils.h"

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

//TODO use template to create spatial hash map of something else than Rendered object
class SpatialHashMap {
    private:
        std::unordered_map<Point, std::vector<Rendered*>, PointHash, PointEqual> buckets_;
        std::set<Point> getBucketsPoints(const Rendered& object);
        bool areHitboxesColliding(const Rendered& p1, const Rendered& p2);
        const static int BUCKET_SIZE = 100;

    public:
        void add(Rendered& object);
        void clear();
        void removeObject(Rendered& object);
        std::vector<Rendered*> checkCollisions(Rendered& object);
};

#endif
