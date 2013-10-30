#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "GraphicEngine.hpp"
#include "GameEngine.hpp"
#include "ContextManager.hpp"

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
  ContextManager contextManager;
};

#endif // APPLICATION_HPP
