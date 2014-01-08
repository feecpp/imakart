#ifndef ITEMLOGIC_HPP
#define ITEMLOGIC_HPP

#include "Positionable.hpp"
#include "BoundingBox.hpp"
#include <string>

class ItemInterface;

class ItemLogic: public Positionable{
public:
  ItemLogic(const std::string oName);
  ItemLogic(const ItemLogic& other);
  ~ItemLogic();

  const glm::vec3& getPosition() const
  	{return position;}

  const glm::quat& getOrientation() const
  	{return orientation;}

  const BoundingBox& getBoundingBox() const
    {return boundingBox;}

  void update();
  void launch(const glm::vec3 positionLauncher, const glm::quat orientationLauncher);

  const std::string getEffect();
  const std::string& getName();

private:
  BoundingBox boundingBox;

  glm::vec3 position;
  glm::quat orientation;

  std::string name;
  std::string effect;
  bool used;

  ItemInterface* myInterface;
};

#endif