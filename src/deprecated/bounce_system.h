//
// Created by meloman on 04.06.17.
//

#ifndef ENTITYXEXAMPLE_BOUNCE_SYSTEM_H
#define ENTITYXEXAMPLE_BOUNCE_SYSTEM_H

#include <entityx/entityx.h>
#include "events/collision_event.h"
#include "components/body.h"


// Bounce entity_body_map off the edge of the screen.
class BounceSystem : public ex::System<BounceSystem>, public ex::Receiver<BounceSystem> {
public:
  explicit BounceSystem(sf::RenderTarget& target) : size(target.getSize()) {}


  void configure(ex::EventManager& events) override;

  void update(ex::EntityManager& es, ex::EventManager& events, ex::TimeDelta dt) override;

  void receive(const CollisionEvent& coll_event);

  static void reverse(float& value);

private:
  sf::Vector2u size;
  std::vector<CollisionEvent> coll_events;
};


#endif //ENTITYXEXAMPLE_BOUNCE_SYSTEM_H
