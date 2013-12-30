#ifndef POSLIGHT_HPP
#define POSLIGHT_HPP

#include <glm/glm.hpp>


class PointLight
{
public:
    PointLight();
    PointLight(glm::vec3 position);
    PointLight(glm::vec3 position, glm::vec3 intensity);

    const glm::vec3 getLightPosition() const;
    const glm::vec3 getLightIntensity() const;
    void updateLight(const glm::mat4 viewMatrix);

private:
  glm::vec3 position;
  glm::vec3 info;
  glm::vec3 intensity;
};

#endif // POSLIGHT_HPP
