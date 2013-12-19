#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include <glm/glm.hpp>

struct BoundingBox
{
  BoundingBox()
    : position(0.f), size(1.f) {}


  bool collideWith(const BoundingBox& other)
  {
    //TODO
    return false;
  }

  glm::vec3 position;
  glm::vec3 size;
};

#endif // BOUNDINGBOX_HPP
