//
// Created by meloman on 04.06.17.
//

#ifndef ENTITYXEXAMPLE_SPAWN_SYSTEM_H
#define ENTITYXEXAMPLE_SPAWN_SYSTEM_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <ctime>
#include <components/shapes.h>
#include <util.h>
#include <events/EntitySpawnedEvent.h>
#include <components/renderable.h>
#include "components/collideable.h"
#include "components/body.h"
#include "common.h"


enum SpawnType {
    SPAWN_SCREEN_TOP,
    SPAWN_SCREEN_CENTER,
    SPAWN_RANDOM
};


class SpawnSystem : public ex::System<SpawnSystem> {
private:
    float time_counter;

    glm::vec2 play_field_size;
    const SpawnType spawn_type;

    const int target_count = 100;   // общее требуемое количество сущностей
    const int spawn_speed = 100;    // сущностей/сек.
    double spawn_now_count = 0;     // количество сущностей, которых надо заспаунить за кадр

    bool big_ball_spawned = false;


    ex::Entity createEntity(ex::EntityManager &es, const glm::vec2 &position) {
        const float MAX_SPEED = 0.5;

        ex::Entity entity = es.create();

        // Mark as collideable
        entity.assign<Collideable>();

        // "Physical" attributes.
        float vel_x = randomizeSign(randomFloatNew(MAX_SPEED/5, MAX_SPEED));
        float vel_y = randomizeSign(randomFloatNew(MAX_SPEED/5, MAX_SPEED));
        glm::vec2 velocity(vel_x, vel_y);
        entity.assign<Body>(position, velocity);

        // Визуальные свойства
        auto color = generateColor(0.7, 0.7);
        entity.assign<Renderable>(color, 0);

        return entity;
    }


    glm::vec2 getSpawnPos(SpawnType spawn_type_) {
        switch (spawn_type_) {

            case SPAWN_SCREEN_TOP:
                return glm::vec2(play_field_size.x / 2, play_field_size.y * 0.9);

            case SPAWN_SCREEN_CENTER:
                return play_field_size / 2.0f;

            case SPAWN_RANDOM:
                return glm::vec2(randomFloatNew(0, play_field_size.x), randomFloatNew(0, play_field_size.y));

            default:  // не должно происходить
                throw std::invalid_argument("Invalid spawn type: " + std::to_string(spawn_type_));
        }
    }


public:
    explicit SpawnSystem(float width, float height, SpawnType spawn_type, int spawn_count, int spawn_speed = 100)
            : play_field_size(width, height), spawn_type(spawn_type), target_count(spawn_count), spawn_speed(spawn_speed) {
        std::srand(std::time(nullptr));  // seed random

        time_counter = 0;
    }


    void update(ex::EntityManager& es, ex::EventManager& events, ex::TimeDelta dt) override {
        int current_count = 0;
        ex::ComponentHandle<Collideable> collideable;
        es.each<Collideable>([&](ex::Entity entity, Collideable&) { ++current_count; });

        spawn_now_count += spawn_speed * dt;
        spawn_now_count = std::min(spawn_now_count, (double)(target_count - current_count));

        for (; spawn_now_count > 0; --spawn_now_count) {
            ex::Entity entity = createEntity(es, getSpawnPos(spawn_type));

            // CircleShape с радиусом
            const float radius = play_field_size.x/200;
            entity.assign<CircleShape>(randomFloatNew(radius / 5, radius));

            events.emit<EntitySpawnedEvent>(entity);
        }

        if (big_ball_spawned)
            return;
        if (target_count == current_count)
            time_counter += dt;
        if (time_counter > 1) {
            big_ball_spawned = true;
            ex::Entity entity = createEntity(es, getSpawnPos(SPAWN_SCREEN_CENTER));

            // CircleShape с радиусом
            const float big_radius = play_field_size.x/35;
            entity.assign<CircleShape>(randomFloatNew(big_radius * 0.8f, big_radius));

            events.emit<EntitySpawnedEvent>(entity);
        }
    }
};


#endif //ENTITYXEXAMPLE_SPAWN_SYSTEM_H
