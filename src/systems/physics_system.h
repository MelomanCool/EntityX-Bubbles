//
// Created by meloman on 04.06.17.
//

#ifndef ENTITYXEXAMPLE_PHYSICS_SYSTEM_H
#define ENTITYXEXAMPLE_PHYSICS_SYSTEM_H

#include <entityx/System.h>
#include <Box2D/Box2D.h>
#include <map>
#include <SFML/Graphics/RenderTarget.hpp>
#include <components/shapes.h>
#include <components/collideable.h>
#include "components/body.h"
#include "events/EntitySpawnedEvent.h"
#include "common.h"


class PhysicsSystem : public ex::System<PhysicsSystem>, public ex::Receiver<PhysicsSystem> {
public:
    explicit PhysicsSystem() : physics_world({0, -9.8f}) {
        physics_world.SetAllowSleeping(false);
    }


    void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) {
        // синхронизация физических тел с телами сущностей
        for (auto &pair : entity_body_map) {
            auto entity = es.get(pair.first);
            auto b2_body = pair.second;

            syncFromEntity(entity, b2_body);
        }

        // simulate physics
        physics_world.Step(dt, velocity_iterations, position_iterations);

        // синхронизация физических тел с телами сущностей
        for (auto &pair : entity_body_map) {
            auto entity = es.get(pair.first);
            auto b2_body = pair.second;

            syncToEntity(entity, b2_body);

        }
    }


    void createBorders(float width, float height) {

        // верхняя и нижняя границы
        createEdge({width / 2, height}, {-width / 2, 0}, {width / 2, 0});
        createEdge({width / 2, 0}, {-width / 2, 0}, {width / 2, 0});

        // левая и правая границы
        createEdge({0, 0}, {0, 0}, {0, height});
        createEdge({width, 0}, {0, 0}, {0, height});
    }


    void configure(ex::EventManager &events) override {
        events.subscribe<EntitySpawnedEvent>(*this);
        events.subscribe<ex::EntityDestroyedEvent>(*this);
    }


    void receive(const EntitySpawnedEvent &entity_spawned_event) {
        auto entity = entity_spawned_event.entity;
        if (not entity.has_component<Collideable>())
            return;

        auto pos = entity.component<Body>()->position;

        auto *b2_body = createB2Body(pos, b2_dynamicBody);

        // здесь можно настраивать fixture для каждой формы сущности
        if (entity.has_component<CircleShape>()) {
            float radius = entity.component<CircleShape>()->radius;
            createCircleShape(radius, b2_body);
        } else {  // мы не умеем обрабатывать сущности с такой формой
            destroyB2Body(b2_body);
            return;
        }

        entity_body_map[entity.id()] = b2_body;
    }


    void receive(const ex::EntityDestroyedEvent &entity_destroyed_event) {
        auto entity_id = entity_destroyed_event.entity.id();

        physics_world.DestroyBody(entity_body_map[entity_id]);
        entity_body_map.erase(entity_id);
    }


    void setGravity(float x, float y) {
        physics_world.SetGravity({x, y});
    }

private:
    b2World physics_world;
    int velocity_iterations = 8;
    int position_iterations = 3;

    std::map<ex::Entity::Id, b2Body *> entity_body_map;

    const float BODY_RESTITUTION = 0.1;
    const int BODY_DENSITY = 1;
    const int BODY_FRICTION = 1;


    void createEdge(const b2Vec2 &pos, const b2Vec2 &line_start, const b2Vec2 &line_end) {
        auto *edge = createB2Body(pos, b2_staticBody);
        createEdgeShape(edge, line_start, line_end);
    }


    void createFixture(b2Body *b2_body, const b2Shape &shape) const {
        b2FixtureDef fixture_def;

        fixture_def.shape = &shape;
        fixture_def.density = BODY_DENSITY;
        fixture_def.restitution = BODY_RESTITUTION;
        fixture_def.friction = BODY_FRICTION;
        b2_body->CreateFixture(&fixture_def);
    }


    void createCircleShape(float radius, b2Body *circle_body) const {
        b2CircleShape circle_shape;

        circle_shape.m_radius = radius;
        createFixture(circle_body, circle_shape);
    }


    void createEdgeShape(b2Body *edge_body, const b2Vec2 &line_start, const b2Vec2 &line_end) const {
        b2EdgeShape edge_shape;

        edge_shape.Set(line_start, line_end);
        createFixture(edge_body, edge_shape);
    }


    template<typename VecXY>
    b2Body *createB2Body(const VecXY &pos, b2BodyType body_type) {
        b2BodyDef b2_body_def;
        b2_body_def.type = body_type;
        b2_body_def.position.Set(pos.x, pos.y);
        b2Body *b2_body = physics_world.CreateBody(&b2_body_def);
        return b2_body;
    }


    void destroyB2Body(b2Body *b2_body) {
        physics_world.DestroyBody(b2_body);
    }


    void syncToEntity(ex::Entity &entity, const b2Body *b2_body) {
        ex::ComponentHandle<Body> body = entity.component<Body>();

        body->position.x = b2_body->GetPosition().x;
        body->position.y = b2_body->GetPosition().y;
        body->velocity.x = b2_body->GetLinearVelocity().x;
        body->velocity.y = b2_body->GetLinearVelocity().y;
        body->rotation = b2_body->GetAngle();
    }


    void syncFromEntity(ex::Entity &entity, b2Body *b2_body) {
        ex::ComponentHandle<Body> body = entity.component<Body>();

        b2_body->SetTransform({body->position.x, body->position.y}, body->rotation);

//        const float EPS = 0.001f;
//        if (glm::length(body->velocity) > EPS)  // игнорируем слишком маленькое ускорение
            b2_body->SetLinearVelocity({body->velocity.x, body->velocity.y});
    }
};


#endif //ENTITYXEXAMPLE_PHYSICS_SYSTEM_H
