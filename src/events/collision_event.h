//
// Created by meloman on 04.06.17.
//

#ifndef ENTITYXEXAMPLE_COLLISION_EVENT_H
#define ENTITYXEXAMPLE_COLLISION_EVENT_H

#include "common.h"


// Emitted when two entities collide.
struct CollisionEvent {
  CollisionEvent(ex::Entity left, entityx::Entity right) : left(left), right(right) {}


  entityx::Entity left, right;
};


#endif //ENTITYXEXAMPLE_COLLISION_EVENT_H
