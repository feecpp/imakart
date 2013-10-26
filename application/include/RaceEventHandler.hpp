#ifndef RACEEVENTHANDLER_HPP
#define RACEEVENTHANDLER_HPP

#include "EventHandler.hpp"

class Game;

class RaceEventHandler : public EventHandler
{

public:
  RaceEventHandler(Game* game);

  virtual void up() const;
  virtual void down() const;
  virtual void left() const;
  virtual void right() const;

private:
  Game* game;

};



#endif // RACEEVENTHANDLER_HPP
