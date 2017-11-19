//
// Created by meloman on 05.06.17.
//

#ifndef ENTITYXEXAMPLE_UTIL_H
#define ENTITYXEXAMPLE_UTIL_H

#include <random>
#include <string>
#include <SFML/Graphics/Font.hpp>
#include <glm/vec3.hpp>

using std::string;


// возвращает случайное значение в диапазоне [min_value+0, min_value+a)
float randomFloat(float min_value, float max_addition);

float randomFloatNew(float min, float max);

template <typename T>
T randomizeSign(T value) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<char> dis(0, 1);
    bool should_change_sign = dis(gen);

    if (should_change_sign)
        return value * (-1);
    else
        return value;
}


typedef glm::uvec3 ColorRgb;

ColorRgb generateColor(float saturation, float value);


sf::Font loadFont(string file_path);

// http://stackoverflow.com/a/87333
class FpsCounter {
private:
  bool first = true;
  float fps = 0;
  const float smoothing = 0.99;

public:
  float update(float timepassed);;
};

#endif //ENTITYXEXAMPLE_UTIL_H
