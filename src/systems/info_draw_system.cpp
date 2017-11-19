//
// Created by meloman on 06.06.17.
//

#include <sstream>
#include "info_draw_system.h"


InfoDrawSystem::InfoDrawSystem(sf::RenderTarget& target, sf::Font& font) : target(target) {
    info_text.setFont(font);
    info_text.setPosition(2, 2);
    info_text.setCharacterSize(18);
    info_text.setFillColor(sf::Color::White);
}


void InfoDrawSystem::update(ex::EntityManager& es, ex::EventManager& events, ex::TimeDelta dt) {
    drawInfo(es.size(), dt);
}


void InfoDrawSystem::drawInfo(int entities_count, float dt) {
    float fps = fps_counter.update(dt);

    std::ostringstream info;
    info << entities_count << " entities (" << static_cast<int>(fps) << " fps)";

    info_text.setString(info.str());
    target.draw(info_text);
}
