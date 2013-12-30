#ifndef DIRLIGHT_HPP
#define DIRLIGHT_HPP

#include <glm/glm.hpp>


class DirectionalLight
{
public:
    DirectionalLight();
    DirectionalLight(glm::vec3 direction);

    const glm::vec3 getLightDirection() const;
    const glm::vec3 getLightIntensity() const;
    void updateLight(const glm::mat4 viewMatrix);


private:
  glm::vec3 direction;
  glm::vec3 intensity;
};

#endif // DIRLIGHT_HPP
