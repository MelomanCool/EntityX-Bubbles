//
// Created by meloman on 05.06.17.
//

#ifndef ENTITYXEXAMPLE_RENDERABLE_H
#define ENTITYXEXAMPLE_RENDERABLE_H

#include <tuple>
#include <memory>
#include <glm/vec3.hpp>

typedef glm::uvec3 Color;


class Renderable {
public:
  Renderable(const Color& color, float alpha) : color(color), alpha(alpha) {}

  Color color;
  float alpha;
};


#endif //ENTITYXEXAMPLE_RENDERABLE_H
