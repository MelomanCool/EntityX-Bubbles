//
// Created by meloman on 04.06.17.
//

#ifndef ENTITYXEXAMPLE_BODY_H
#define ENTITYXEXAMPLE_BODY_H

#include <glm/glm.hpp>


struct Body {
    Body(const glm::vec2& position, const glm::vec2& velocity, float rotation = 0)
            : position(position), velocity(velocity), rotation(rotation) {
    }


    glm::vec2 position;
    glm::vec2 velocity;
    float rotation = 0.0;
};


#endif //ENTITYXEXAMPLE_BODY_H
