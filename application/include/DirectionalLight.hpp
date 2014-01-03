#ifndef DIRLIGHT_HPP
#define DIRLIGHT_HPP

#include <glm/glm.hpp>


class DirectionalLight
{
public:
    DirectionalLight();
    DirectionalLight(glm::vec4 direction);

    const glm::vec4 getLightDirection() const;
    const glm::vec3 getLightIntensity() const;
    void updateLight(const glm::mat4 viewMatrix);


private:
  glm::vec4 direction;
  glm::vec3 intensity;
};

#endif // DIRLIGHT_HPP
