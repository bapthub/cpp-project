//#ifndef PROJECT_SDL1_SPATIALHASHMAP_H
//#define PROJECT_SDL1_SPATIALHASHMAP_H
//
//#include <unordered_map>
//#include <set>
//#include <vector>
//#include "../SDL/Animal.h"
//#include "./Point.h"
//#include "../Utils/Utils.h"
//
//struct PointHash {
//    std::size_t operator()(const Point& p) const {
//        return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
//    }
//};
//
//struct PointEqual {
//    bool operator()(const Point& p1, const Point& p2) const {
//        return p1.x == p2.x && p1.y == p2.y;
//    }
//};
//
////TODO use template to create spatial hash map of something else than Animal object
//template <typename T>
//class SpatialHashMap {
//private:
//    std::unordered_map<Point, std::vector<T*>, PointHash, PointEqual> buckets_;
//    std::set<Point> getBucketsPoints(const T& object)
//    {
//        std::set<Point> keySet;
//        keySet.insert({(object.point.x - object.w_size / 2) / SpatialHashMap::BUCKET_SIZE, (object.point.y - object.h_size / 2) / SpatialHashMap::BUCKET_SIZE});
//        keySet.insert({(object.point.x - object.w_size / 2) / SpatialHashMap::BUCKET_SIZE, (object.point.y + object.h_size / 2) / SpatialHashMap::BUCKET_SIZE});
//        keySet.insert({(object.point.x + object.w_size / 2) / SpatialHashMap::BUCKET_SIZE, (object.point.y - object.h_size / 2) / SpatialHashMap::BUCKET_SIZE});
//        keySet.insert({(object.point.x + object.w_size / 2) / SpatialHashMap::BUCKET_SIZE, (object.point.y + object.h_size / 2) / SpatialHashMap::BUCKET_SIZE});
//
//        return keySet;
//    }
//
//    bool areHitboxesColliding(const T& p1, const T& p2)
//    {
//        return
//                p1.point.x < p2.point.x + p2.w_size &&
//                p1.point.x + p1.w_size > p2.point.x &&
//                p1.point.y < p2.point.y + p2.h_size &&
//                p1.point.y + p1.h_size > p2.point.y;
//    }
//
//    const static int BUCKET_SIZE = 100;
//
//public:
//    void add(T& object)
//    {
//        auto keySet = this->getBucketsPoints(object);
//
//        for(auto point: keySet) {
//            this->buckets_[point].push_back(&object);
//        }
//    }
//
//    void clear()
//    {
//        for(auto& bucket: buckets_)
//        {
//            bucket.second.clear();
//        }
//    }
//
//    void removeObject(T& object)
//    {
//        auto keySet = this->getBucketsPoints(object);
//
//        for(auto key: keySet) {
//            Utils::removeFromVector(this->buckets_[key], &object);
//        }
//    }
//
//    std::vector<Animal*> checkCollisions(T& object)
//    {
//        std::vector<T*> collisions;
//
//        auto keySet = this->getBucketsPoints(object);
//
//        for(auto key: keySet) {
//            for(auto target: this->buckets_[key]) {
//                if (
//                        target != &object &&
//                        this->areHitboxesColliding(*target, object) &&
//                        std::count(collisions.begin(), collisions.end(), target) == 0
//                        ) {
//                    collisions.push_back(target);
//                }
//            }
//        }
//
//        return collisions;
//
//    };
//
//#endif



#ifndef PROJECT_SDL1_SPATIALHASHMAP_H
#define PROJECT_SDL1_SPATIALHASHMAP_H

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

//TODO use template to create spatial hash map of something else than Animal object
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

#endif
