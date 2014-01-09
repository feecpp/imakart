#ifndef POSLIGHT_HPP
#define POSLIGHT_HPP

#include <glm/glm.hpp>


class PointLight
{
public:
  PointLight();
  PointLight(glm::vec4 position);
  PointLight(glm::vec4 position, glm::vec3 intensity);

  const glm::vec4 getLightPosition() const;
  const glm::vec3 getLightIntensity() const;
  void updateLight(const glm::mat4 viewMatrix);

private:
  glm::vec4 position;
  glm::vec4 info;
  glm::vec3 intensity;
};

#endif // POSLIGHT_HPP
