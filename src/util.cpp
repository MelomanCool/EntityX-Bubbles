//
// Created by meloman on 05.06.17.
//

#include <random>
#include <stdexcept>
#include <glm/gtc/constants.hpp>
#include <glm/common.hpp>
#include "util.h"


using glm::operator%;

const float golden_ratio_conjugate = glm::golden_ratio<float>()-1;


float randomFloat(float min_value, float max_addition) {
    return (rand() % (int)(max_addition * 1000) + min_value * 1000) / 1000.0f;
}


float randomFloatNew(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}


sf::Font loadFont(string file_path) {
    sf::Font font;

    if (!font.loadFromFile(file_path))
        throw std::invalid_argument("failed to load " + file_path);

    return font;
}

ColorRgb generateColor(float saturation, float value) {
    static double hue = randomFloatNew(0, 6);

    hue += golden_ratio_conjugate;
    hue = fmod(hue, 6);

    int int_hue = int(hue);
    double f = hue - int_hue;

    double p = value * (1 - saturation);
    double q = value * (1 - f*saturation);
    double t = value * (1 - (1 - f) * saturation);

    glm::vec3 color;
    if (int_hue == 0)
        color = glm::vec3(value, t, p);
    if (int_hue == 1)
        color = glm::vec3(q, value, p);
    if (int_hue == 2)
        color = glm::vec3(p, value, t);
    if (int_hue == 3)
        color = glm::vec3(p, q, value);
    if (int_hue == 4)
        color = glm::vec3(t, p, value);
    if (int_hue == 5)
        color = glm::vec3(value, p, q);

    return color *= 255.0;
}


float FpsCounter::update(float timepassed) {
    float current = 1 / timepassed;

    if (first) {
        first = false;
        fps = current;
        return fps;
    }

    fps = (fps * smoothing) + (current * (1.0f - smoothing));
    return fps;
}
