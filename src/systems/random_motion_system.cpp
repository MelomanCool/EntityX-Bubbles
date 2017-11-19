//
// Created by meloman on 05.06.17.
//

#include "random_motion_system.h"


void RandomMotionSystem::update(ex::EntityManager& es, ex::EventManager& events, ex::TimeDelta dt) {

  es.each<Body>([this, dt](entityx::Entity, Body& body) {
    if (randomFloat(0, 1) < impulce_probability * dt)
      accelerateRandom(body);
  });

}


void RandomMotionSystem::accelerateRandom(Body& body) {
  body.velocity = {randomFloatNew(-10, 10), randomFloatNew(-10, 10)};
}
