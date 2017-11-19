//
// Created by meloman on 05.06.17.
//

#ifndef ENTITYXEXAMPLE_RANDOM_MOTION_SYSTEM_H
#define ENTITYXEXAMPLE_RANDOM_MOTION_SYSTEM_H


#include <entityx/System.h>
#include "components/body.h"
#include "common.h"
#include "util.h"

class RandomMotionSystem : public ex::System<RandomMotionSystem> {
private:
  const float impulce_probability = 0.1;  // вероятность срабатывания за секунду

public:
  explicit RandomMotionSystem() {};

  void update(ex::EntityManager& es, ex::EventManager& events, ex::TimeDelta dt) override;

  void accelerateRandom(Body& body);
};


#endif //ENTITYXEXAMPLE_RANDOM_MOTION_SYSTEM_H
