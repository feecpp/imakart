#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "GraphicEngine.hpp"

class GameEngine;

class Application
{
public:
  Application(GameEngine& gameEngine);

  void setupEverything();
  void startGame();

  bool handleEvents();

private:
  GameEngine& gameEngine;
  GraphicEngine graphicEngine;
};

#endif // APPLICATION_HPP
