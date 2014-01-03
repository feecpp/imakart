#ifndef ITEMGENERATOR_HPP
#define ITEMGENERATOR_HPP

#include <glm/glm.hpp>
#include "BoundingBox.hpp"
#include "Positionable.hpp"
#include <iostream>

class ItemLogic;
class ItemBox;

class ItemGenerator: public Positionable{
public:
  ItemGenerator(const glm::vec3 position);
  ~ItemGenerator();

  const glm::vec3& getPosition() const
  	{return itemPosition;}

  const glm::quat& getOrientation() const
  	{return itemOrientation;}

  const BoundingBox& getBoundingBox() const
    {return boundingBox;}

  ItemLogic* getRandomItem() const;

private:
  glm::vec3 itemPosition;
  glm::quat itemOrientation;

  ItemBox* itemBox;
  BoundingBox boundingBox;
};

#endif