//
// Created by meloman on 04.06.17.
//

#ifndef ENTITYXEXAMPLE_OPACITY_SYSTEM_H
#define ENTITYXEXAMPLE_OPACITY_SYSTEM_H

#include <algorithm>
#include <entityx/entityx.h>
#include "components/body.h"
#include "common.h"


// Updates alpha body's opacity.
struct OpacitySystem : public entityx::System<OpacitySystem> {
  void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override;;
};


#endif //ENTITYXEXAMPLE_OPACITY_SYSTEM_H
