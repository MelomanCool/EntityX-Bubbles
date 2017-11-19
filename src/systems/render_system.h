//
// Created by meloman on 04.06.17.
//

#ifndef ENTITYXEXAMPLE_RENDER_SYSTEM_H
#define ENTITYXEXAMPLE_RENDER_SYSTEM_H


#include <sstream>
#include <map>
#include <SFML/Graphics.hpp>

#include "components/body.h"
#include "events/collision_event.h"
#include "events/EntitySpawnedEvent.h"
#include "util.h"
#include "common.h"

typedef std::shared_ptr<sf::Shape> shape_shared_ptr;


// Renders all shape_shared_ptr entities and draws some informational text.
class RenderSystem : public ex::System<RenderSystem>, public ex::Receiver<RenderSystem> {
public:
  explicit RenderSystem(sf::RenderTarget& target, sf::Font& font);

  void update(ex::EntityManager& es, ex::EventManager& events, ex::TimeDelta dt) override;

  void configure(ex::EventManager& events) override;

  void receive(const EntitySpawnedEvent& entity_spawned_event);

  void receive(const ex::EntityDestroyedEvent& entity_destroyed_event);

  void setShouldDrawPos(bool flag);

private:
  sf::Text pos_text;
  sf::RenderTarget& target;
  bool should_draw_pos = false;
  std::map<ex::Entity::Id, shape_shared_ptr> entity_shape_map;


  shape_shared_ptr createSfCircleShape(ex::Entity entity);

  void drawEntity(ex::Entity entity, shape_shared_ptr sf_shape);

  void drawTextAtPos(const std::string& info, const sf::Vector2f& pos);

  void drawPosInfo(const ex::ComponentHandle <Body> body, const shape_shared_ptr sf_shape);
};


#endif //ENTITYXEXAMPLE_RENDER_SYSTEM_H
