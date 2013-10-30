#ifndef CONTEXTMANAGER_HPP
#define CONTEXTMANAGER_HPP

#include "RaceEventHandler.hpp"
#include "MenuEventHandler.hpp"

class GameEngine;
class GraphicEngine;

class ContextManager
{
public:
  ContextManager(GameEngine& gameEngine, GraphicEngine& graphicEngine);

  void setupMenuContext() const;
  void setupRaceContext() const;

  const EventHandler& getHandler() const;

private:
  GameEngine& gameEngine;
  GraphicEngine& graphicEngine;
  RaceEventHandler raceEventHandler;
  MenuEventHandler menuEventHandler;
};

#endif // CONTEXTMANAGER_HPP
