//
// Created by meloman on 04.06.17.
//

#include "opacity_system.h"
#include "components/renderable.h"


void OpacitySystem::update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) {
  const float fdt = static_cast<float>(dt);
  es.each<Renderable>([fdt](entityx::Entity entity, Renderable& renderable) {
    renderable.alpha = std::min(1.0f, renderable.alpha + fdt);
  });
}
