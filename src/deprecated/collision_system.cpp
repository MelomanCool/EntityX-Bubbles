//
// Created by meloman on 04.06.17.
//

#include "collision_system.h"


CollisionSystem::CollisionSystem(sf::RenderTarget& target) : size(target.getSize()) {
    size.x = size.x / PARTITIONS + 1;
    size.y = size.y / PARTITIONS + 1;
}


void CollisionSystem::update(ex::EntityManager& es, ex::EventManager& events, ex::TimeDelta dt) {
    reset();
    collect(es);
    collide(events);
}


void CollisionSystem::reset() {
    grid.clear();
    grid.resize(size.x * size.y);
}


void CollisionSystem::collect(ex::EntityManager& entities) {
    entities.each<Body, Collideable>([this](ex::Entity entity, Body& body, Collideable& collideable) {
        int    left = static_cast<int>(body.position.x - collideable.radius) / PARTITIONS;
        int top = static_cast<int>(body.position.y - collideable.radius) / PARTITIONS;
        int right = static_cast<int>(body.position.x + collideable.radius) / PARTITIONS;
        int bottom = static_cast<int>(body.position.y + collideable.radius) / PARTITIONS;
        Candidate candidate{body.position, collideable.radius, entity};
        unsigned int slots[4] = {
                left + top * size.x,
                right + top * size.x,
                left + bottom * size.x,
                right + bottom * size.x,
        };
        grid[slots[0]].push_back(candidate);
        if (slots[0] != slots[1]) grid[slots[1]].push_back(candidate);
        if (slots[1] != slots[2]) grid[slots[2]].push_back(candidate);
        if (slots[2] != slots[3]) grid[slots[3]].push_back(candidate);
    });
}


void CollisionSystem::collide(ex::EventManager& events) {
    for (const std::vector<Candidate>& candidates : grid) {
        for (auto left = candidates.begin(); left != candidates.end(); left++) {
            for (auto right = left + 1; right != candidates.end(); right++) {
                if (collided(*left, *right))
                    events.emit<CollisionEvent>(left->entity, right->entity);
            }
        }
    }
}


bool CollisionSystem::collided(const CollisionSystem::Candidate& left, const CollisionSystem::Candidate& right) {
    return length(left.position - right.position) < left.radius + right.radius;
}


float CollisionSystem::length(const sf::Vector2f& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}
