#ifndef MENUEVENTHANDLER_HPP
#define MENUEVENTHANDLER_HPP

#include "EventHandler.hpp"
#include "MenuLogic.hpp"

class GameEngine;
class GraphicEngine;

class MenuEventHandler : public EventHandler
{
public:
  MenuEventHandler(GameEngine& gameEngine, GraphicEngine& graphicEngine);

  virtual void pressUp() const;
  virtual void pressDown() const;
  virtual void pressLeft() const;
  virtual void pressRight() const;
  virtual void pressEnter() const;
  virtual void pressSpace() const;
  virtual void releaseUp() const;
  virtual void releaseDown() const;
  virtual void releaseLeft() const;
  virtual void releaseRight() const;
  virtual void releaseEnter() const;
  virtual void releaseSpace() const;
  virtual void pressNumpad0() const;
  virtual void releaseNumpad0() const;

  void setMenu(MenuLogic* menu)
   	{this->menu = menu;}

private:
  GameEngine& gameEngine;
  GraphicEngine& graphicEngine;
  MenuLogic* menu;
};

#endif // MENUEVENTHANDLER_HPP
