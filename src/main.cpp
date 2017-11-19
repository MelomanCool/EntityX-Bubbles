#include "systems/spawn_system.h"
#include "systems/opacity_system.h"
#include "systems/render_system.h"
#include "systems/physics_system.h"
#include "systems/random_motion_system.h"
#include "systems/info_draw_system.h"
#include "systems/gravity_system.h"
#include "common.h"

#include <SFML/Window.hpp>
#include <entityx/entityx.h>


class EcsManager : public entityx::EntityX {
public:
    explicit EcsManager(sf::RenderTarget& target, sf::Font& font) {
        float width = target.getSize().x / PIXEL_PER_METRE;
        float height = target.getSize().y / PIXEL_PER_METRE;

        // можно закомментировать любую систему чтобы её отключить
        systems.add<SpawnSystem>(width, height, SPAWN_RANDOM, 300);
        systems.add<PhysicsSystem>();
//        systems.add<RandomMotionSystem>();
        systems.add<OpacitySystem>();
        systems.add<RenderSystem>(target, font);
        systems.add<InfoDrawSystem>(target, font);
        systems.add<GravitySystem>();

        systems.configure();


        // необязательные настройки
        systems.system<PhysicsSystem>()->createBorders(width, height);
        systems.system<PhysicsSystem>()->setGravity(0, 0);

//        systems.system<RenderSystem>()->setShouldDrawPos(true);
    }


    void update(ex::TimeDelta dt) {
        ex::TimeDelta fast_dt = dt * 10;

        systems.update<SpawnSystem>(fast_dt);

//        systems.update<RandomMotionSystem>(fast_dt);
//        systems.update<GravitySystem>(fast_dt);
        systems.update<PhysicsSystem>(fast_dt);

        systems.update<OpacitySystem>(fast_dt);
        systems.update<RenderSystem>(fast_dt);
        systems.update<InfoDrawSystem>(dt);
    }
};


int main() {
//  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "EntityX Box2D Example", sf::Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "EntityX Box2D Example", sf::Style::Default, sf::ContextSettings(24,8,8));
    sf::Font font = loadFont("res/LiberationSans-Regular.ttf");

    EcsManager manager(window, font);

    sf::Clock clock;

    // основной цикл отрисовки
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
//        case sf::Event::KeyPressed:
                    window.close();
                    break;

                default:
                    break;
            }
        }

        window.clear();
        sf::Time elapsed = clock.restart();
        manager.update(elapsed.asSeconds());
        window.display();
    }
}
