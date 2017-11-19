//
// Created by meloman on 04.06.17.
//

#include "render_system.h"
#include "events/EntitySpawnedEvent.h"
#include "components/collideable.h"
#include "util.h"
#include "components/renderable.h"
#include "components/shapes.h"


RenderSystem::RenderSystem(sf::RenderTarget& target, sf::Font& font) : target(target) {
  pos_text.setFont(font);
  pos_text.setPosition(0, 0);
  pos_text.setCharacterSize(18);
  pos_text.setFillColor(sf::Color::White);
}


void RenderSystem::update(ex::EntityManager& es, ex::EventManager& events, ex::TimeDelta dt) {

  for (auto& pair : entity_shape_map) {
    drawEntity(es.get(pair.first), pair.second);
  }
}


void RenderSystem::drawEntity(ex::Entity entity, shape_shared_ptr sf_shape) {
  auto renderable = entity.component<Renderable>();
  auto body = entity.component<Body>();

  sf_shape->setFillColor(sf::Color(
      renderable->color.r,
      renderable->color.g,
      renderable->color.b,
      renderable->alpha * 255
  ));
  sf_shape->setPosition(body->position.x * PIXEL_PER_METRE, target.getSize().y - body->position.y * PIXEL_PER_METRE);
  sf_shape->setRotation(body->rotation);

  target.draw(*sf_shape);

  // debug
  if (should_draw_pos)
    drawPosInfo(body, sf_shape);
}


void RenderSystem::drawPosInfo(const ex::ComponentHandle <Body> body, const shape_shared_ptr sf_shape) {
  std::ostringstream pos_info;
  pos_info << (int)body->position.x << "," << (int)body->position.y;
  drawTextAtPos(pos_info.str(), sf_shape->getPosition());
}


void RenderSystem::drawTextAtPos(const std::string& info, const sf::Vector2f& pos) {
  pos_text.setString(info);

  // центруем
  auto bounds = pos_text.getLocalBounds();
  pos_text.setOrigin(bounds.width/2, bounds.height/2);

  pos_text.setPosition(pos.x, pos.y);

  target.draw(pos_text);
}


void RenderSystem::configure(ex::EventManager& events) {
  events.subscribe<EntitySpawnedEvent>(*this);
  events.subscribe<ex::EntityDestroyedEvent>(*this);
}


void RenderSystem::receive(const EntitySpawnedEvent& entity_spawned_event) {
  ex::Entity entity = entity_spawned_event.entity;

  // создаем SF-объекты только для сущностей с Renderable
  if (not entity.has_component<Renderable>())
    return;

  shape_shared_ptr sf_shape;

  // здесь можно настраивать, как отображается каждая форма Shape
  if (entity.has_component<CircleShape>()) {
    sf_shape = createSfCircleShape(entity);
    // добавление в мапу пар "id сущности - форма SF"
  } else
    return;  // мы не умеем рисовать сущности с такой формой

  entity_shape_map[entity.id()] = sf_shape;
}


shape_shared_ptr RenderSystem::createSfCircleShape(ex::Entity entity) {
  auto radius = entity.component<CircleShape>()->radius;
  auto position = entity.component<Body>()->position;

  shape_shared_ptr sf_shape(new sf::CircleShape(radius * PIXEL_PER_METRE));
  sf_shape->setOrigin(radius * PIXEL_PER_METRE, radius * PIXEL_PER_METRE);
  sf_shape->setPosition(position.x, target.getSize().y-position.y);

  return sf_shape;
}


void RenderSystem::receive(const ex::EntityDestroyedEvent& entity_destroyed_event) {
  auto entity_id = entity_destroyed_event.entity.id();
  entity_shape_map.erase(entity_id);
}


void RenderSystem::setShouldDrawPos(bool flag) {
  should_draw_pos = flag;
}
