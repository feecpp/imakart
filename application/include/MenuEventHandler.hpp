#ifndef MENUEVENTHANDLER_HPP
#define MENUEVENTHANDLER_HPP

#include "EventHandler.hpp"
#include "MenuLogic.hpp"

class GameEngine;

class MenuEventHandler : public EventHandler
{
public:
  MenuEventHandler(GameEngine* gameEngine);

  virtual void up() const;
  virtual void down() const;
  virtual void left() const;
  virtual void right() const;

  void setMenu(MenuLogic* menu)
   	{this->menu = menu;}

private:
  GameEngine* gameEngine;
  MenuLogic* menu;
};

#endif // MENUEVENTHANDLER_HPP
