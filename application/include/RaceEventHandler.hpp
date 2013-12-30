#ifndef RACEEVENTHANDLER_HPP
#define RACEEVENTHANDLER_HPP

#include "EventHandler.hpp"

class GameEngine;
class GraphicEngine;

class RaceEventHandler : public EventHandler
{

public:
  RaceEventHandler(GameEngine& gameEngine, GraphicEngine& graphicEngine);

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

private:
  GameEngine& gameEngine;
  GraphicEngine& graphicEngine;

};



#endif // RACEEVENTHANDLER_HPP
