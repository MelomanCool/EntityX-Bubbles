//
// Created by meloman on 04.06.17.
//

#include "bounce_system.h"


void BounceSystem::update(ex::EntityManager& es, ex::EventManager& events, ex::TimeDelta dt) {
  es.each<Body>([this](ex::Entity entity, Body& body) {
    if (body.position.x + body.velocity.x < 0 ||
        body.position.x + body.velocity.x >= size.x)
      reverse(body.velocity.x);
    if (body.position.y + body.velocity.y < 0 ||
        body.position.y + body.velocity.y >= size.y)
      reverse(body.velocity.y);
  });

  for (CollisionEvent& coll_event : coll_events) {
    ex::ComponentHandle<Body> left_body = coll_event.left.component<Body>();
    ex::ComponentHandle<Body> right_body = coll_event.right.component<Body>();

    sf::Vector2f temp = left_body->velocity;
    left_body->velocity = right_body->velocity;
    right_body->velocity = temp;
  }
  coll_events.clear();
}


void BounceSystem::receive(const CollisionEvent& coll_event) {
  // Events are immutable, so we can't swap velocities of the entities here.
  // We defer the work until the update loop.
  coll_events.push_back(coll_event);
}


void BounceSystem::configure(ex::EventManager& events) {
  events.subscribe<CollisionEvent>(*this);
}


void BounceSystem::reverse(float& value) {
  value = -value;
}
