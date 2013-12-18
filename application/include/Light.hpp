#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>

class Light {
public:
    Light();
    Light(glm::vec3 direction);

    const glm::vec3 getLighDirection() const;
    const glm::vec3 getLightPosition() const;
    const glm::vec3 getLightIntensity() const;
    void updateLightDirection();
    void updateLight(const glm::mat4 viewMatrix);

private:
  glm::vec3 direction;
  glm::vec3 position;
  glm::vec3 intensity;
};

#endif // LIGHT_HPP
