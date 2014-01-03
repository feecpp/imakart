#ifndef ITEMGENERATOR_HPP
#define ITEMGENERATOR_HPP

#include <glm/glm.hpp>
#include "BoundingBox.hpp"

class ItemLogic;
class ItemBox;

class ItemGenerator{
public:
  ItemGenerator(const glm::vec3 position);
  ~ItemGenerator();

  const BoundingBox& getBoundingBox() const
    {return boundingBox;}

  ItemLogic* getRandomItem() const;

private:
  glm::vec3 itemPosition;

  ItemBox* itemBox;
  BoundingBox boundingBox;
};

#endif