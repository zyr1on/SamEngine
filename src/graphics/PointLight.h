#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <glm/glm.hpp>

struct PointLight {
    glm::vec3 color;
    float intensity;

    PointLight(const glm::vec3& color = glm::vec3(1.0f), float intensity = 1.0f)
        : color(color), intensity(intensity) {}
};

#endif