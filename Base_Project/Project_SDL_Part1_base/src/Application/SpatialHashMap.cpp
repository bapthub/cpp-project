#include "SpatialHashMap.h"

void SpatialHashMap::add(Rendered& object)
{
    auto keySet = this->getBucketsPoints(object);

    for(auto point: keySet) {
        this->buckets_[point].push_back(&object);
    }
}

std::vector<Rendered*> SpatialHashMap::checkCollisions(Rendered& object)
{
    std::vector<Rendered*> collisions;

    auto keySet = this->getBucketsPoints(object);

    for(auto key: keySet) {
        for(auto target: this->buckets_[key]) {
            if (
                    target != &object &&
                    this->areHitboxesColliding(*target, object) &&
                    std::count(collisions.begin(), collisions.end(), target) == 0
            ) {
                collisions.push_back(target);
            }
        }
    }

    return collisions;
}

std::set<Point> SpatialHashMap::getBucketsPoints(const Rendered& object)
{
    std::set<Point> keySet;
    keySet.insert({(object.point.x - object.w_size / 2) / SpatialHashMap::BUCKET_SIZE, (object.point.y - object.h_size / 2) / SpatialHashMap::BUCKET_SIZE});
    keySet.insert({(object.point.x - object.w_size / 2) / SpatialHashMap::BUCKET_SIZE, (object.point.y + object.h_size / 2) / SpatialHashMap::BUCKET_SIZE});
    keySet.insert({(object.point.x + object.w_size / 2) / SpatialHashMap::BUCKET_SIZE, (object.point.y - object.h_size / 2) / SpatialHashMap::BUCKET_SIZE});
    keySet.insert({(object.point.x + object.w_size / 2) / SpatialHashMap::BUCKET_SIZE, (object.point.y + object.h_size / 2) / SpatialHashMap::BUCKET_SIZE});

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

void SpatialHashMap::clear()
{
    for(auto& bucket: buckets_)
    {
        bucket.second.clear();
    }
}

void SpatialHashMap::removeObject(Rendered& object)
{
    auto keySet = this->getBucketsPoints(object);

    for(auto key: keySet) {
        Utils::removeFromVector(this->buckets_[key], &object);
    }
}
