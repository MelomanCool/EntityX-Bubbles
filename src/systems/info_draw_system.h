//
// Created by meloman on 06.06.17.
//

#ifndef ENTITYXBOX2D_INFODRAWSYSTEM_H
#define ENTITYXBOX2D_INFODRAWSYSTEM_H


#include <entityx/System.h>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "util.h"
#include "common.h"


class InfoDrawSystem : public ex::System<InfoDrawSystem> {
private:
  sf::RenderTarget& target;
  FpsCounter fps_counter;
  sf::Text info_text;

  void drawInfo(int entities_count, float dt);

public:
  explicit InfoDrawSystem(sf::RenderTarget& target, sf::Font& font);

  void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta dt) override;
};


#endif //ENTITYXBOX2D_INFODRAWSYSTEM_H
