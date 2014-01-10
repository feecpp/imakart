#ifndef CURSORPLAYERINTERFACE_HPP
#define CURSORPLAYERINTERFACE_HPP

#include "InterfaceElement.hpp"
#include "Kart.hpp"
#include <glm/glm.hpp>
#include <string>

class CursorPlayerInterface: public InterfaceElement{
public:
  CursorPlayerInterface(const glm::vec3& kartOfPlayer);
  ~CursorPlayerInterface();
  const bool isSelected() const;
  const glm::vec3 getPosition() const;

private:
  const glm::vec3& kartPlayer;
};

#endif
