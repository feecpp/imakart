#include "CursorPlayerInterface.hpp"

CursorPlayerInterface::CursorPlayerInterface(const glm::vec3& kartOfPlayer)
  :kartPlayer(kartOfPlayer){}

CursorPlayerInterface::~CursorPlayerInterface(){}

const glm::vec3 CursorPlayerInterface::getPosition() const{
  return kartPlayer;
}

const bool CursorPlayerInterface::isSelected() const
  {return false;}