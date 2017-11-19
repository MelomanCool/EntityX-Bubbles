//
// Created by meloman on 05.06.17.
//

#ifndef ENTITYXEXAMPLE_ENTITY_SPAWNED_H
#define ENTITYXEXAMPLE_ENTITY_SPAWNED_H


#include <entityx/Entity.h>

class EntitySpawnedEvent {
public:
  EntitySpawnedEvent(entityx::Entity entity) : entity(entity) {}


  entityx::Entity entity;
};


#endif //ENTITYXEXAMPLE_ENTITY_SPAWNED_H
