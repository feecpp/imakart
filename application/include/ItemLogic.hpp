#ifndef ITEMLOGIC_HPP
#define ITEMLOGIC_HPP

#include "Positionable.hpp"
#include <string>

class ItemInterface;

class ItemLogic{
public:
  ItemLogic(const std::string oName);
  ~ItemLogic();

  void update();

  const std::string getEffect();
  const std::string& getName();

private:
  std::string name;
  std::string effect;
  bool used;

  ItemInterface* myInterface;
};

#endif