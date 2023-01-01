#include "SpatialHashMap.h"

void SpatialHashMap::add(std::shared_ptr<Rendered> object)
{
    auto keySet = this->getBucketsPoints(object);

    for(auto point: keySet) {
        this->buckets_[point].push_back(object);
    }
}

std::vector<std::shared_ptr<Rendered>> SpatialHashMap::checkCollisions(std::shared_ptr<Rendered> object)
{
    std::vector<std::shared_ptr<Rendered>> collisions;

    auto keySet = this->getBucketsPoints(object);

    for(auto key: keySet) {
        for(auto target: this->buckets_[key]) {
            if (this->areHitboxesColliding(*target, *object)) {
                collisions.push_back(target);
            }
        }
    }

    return collisions;
}

std::set<Point> SpatialHashMap::getBucketsPoints(std::shared_ptr<Rendered> object)
{
    std::set<Point> keySet;
    keySet.insert({(object->point.x - object->w_size / 2) / this->BUCKET_SIZE, (object->point.y - object->h_size / 2) / this->BUCKET_SIZE});
    keySet.insert({(object->point.x - object->w_size / 2) / this->BUCKET_SIZE, (object->point.y + object->h_size / 2) / this->BUCKET_SIZE});
    keySet.insert({(object->point.x + object->w_size / 2) / this->BUCKET_SIZE, (object->point.y - object->h_size / 2) / this->BUCKET_SIZE});
    keySet.insert({(object->point.x + object->w_size / 2) / this->BUCKET_SIZE, (object->point.y + object->h_size / 2) / this->BUCKET_SIZE});

    return keySet;
}

bool SpatialHashMap::areHitboxesColliding(const Rendered& p1, const Rendered& p2)
{
    return
        p1.point.x < p2.point.x + p2.w_size &&
        p1.point.x + p1.w_size > p2.point.x &&
        p1.point.y < p2.point.y + p2.h_size &&
        p1.point.y + p1.h_size > p2.point.y;
}
