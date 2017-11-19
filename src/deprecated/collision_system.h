//
// Created by meloman on 04.06.17.
//

#ifndef ENTITYXEXAMPLE_COLLISION_SYSTEM_H
#define ENTITYXEXAMPLE_COLLISION_SYSTEM_H


#include <cmath>
#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

#include "components/body.h"
#include "components/collideable.h"
#include "events/collision_event.h"


// Determines if two Collideable have collided. If they have it emits a
// CollisionEvent. This is used by ExplosionSystem to create explosion
// particles, but it could be used by a SoundSystem to play an explosion
// sound, etc..
//
// Uses a fairly rudimentary 2D partition system, but performs reasonably well.
class CollisionSystem : public entityx::System<CollisionSystem> {
  static const int PARTITIONS = 200;

  struct Candidate {
    sf::Vector2f position;
    float radius;
    entityx::Entity entity;
  };

public:
  explicit CollisionSystem(sf::RenderTarget& target);

  void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override;

private:
  std::vector<std::vector<Candidate>> grid;
  sf::Vector2u size;

  void reset();

  void collect(entityx::EntityManager& entities);

  void collide(entityx::EventManager& events);

  float length(const sf::Vector2f& v);

  bool collided(const Candidate& left, const Candidate& right);
};


#endif //ENTITYXEXAMPLE_COLLISION_SYSTEM_H
