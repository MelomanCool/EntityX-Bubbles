//
// Created by meloman on 14.06.17.
//

#ifndef ENTITYXBOX2D_GRAVITYSYSTEM_H
#define ENTITYXBOX2D_GRAVITYSYSTEM_H


#include <components/mass.h>
#include <components/body.h>
#include <components/shapes.h>
#include <glm/gtc/constants.hpp>
#include "events/EntitySpawnedEvent.h"
#include "common.h"

using glm::pi;


class GravitySystem : public ex::System<GravitySystem>, public ex::Receiver<GravitySystem> {
public:
    explicit GravitySystem() {}


    void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) {
        es.each<Body, Mass>([&](entityx::Entity left, Body& left_body, Mass& left_mass) {
            es.each<Body, Mass>([&](entityx::Entity right, Body& right_body, Mass& right_mass) {
                if (left == right)
                    return;

                applyGravityForce(left_body, right_body, left_mass, right_mass, dt);
            });
        });
    }


    void configure(ex::EventManager &events) override {
        events.subscribe<EntitySpawnedEvent>(*this);
    }


    void receive(const EntitySpawnedEvent &entity_spawned_event) {
        auto entity = entity_spawned_event.entity;
        float r = entity.component<CircleShape>()->radius;
        entity.assign<Mass>(pi<float>() * r*r);
    }


private:
    void applyGravityForce(Body& left_body, Body& right_body, Mass& left_mass, Mass& right_mass, ex::TimeDelta dt) {
        auto r = left_body.position - right_body.position;
        auto gravity_force = -9.8f * glm::normalize(r) * (left_mass.value * right_mass.value) / glm::length(r)*glm::length(r);
        left_body.velocity += gravity_force * 0.001f * dt;
    }
};


#endif //ENTITYXBOX2D_GRAVITYSYSTEM_H
