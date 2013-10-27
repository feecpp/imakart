#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "GraphicEngine.hpp"
#include "GameEngine.hpp"

class Application
{
public:
  Application();

  void setupEverything();
  void startGame();

private:
  bool handleEvents();

  GameEngine gameEngine;
  GraphicEngine graphicEngine;
};

#endif // APPLICATION_HPP
