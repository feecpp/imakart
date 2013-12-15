#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>

struct Light {
public:
    Light();

    const glm::vec3 getLighDirection() const;
    const glm::vec3 getLightIntensity() const;

private:
  glm::vec3 direction;
  glm::vec3 intensity;
};

#endif // LIGHT_HPP
