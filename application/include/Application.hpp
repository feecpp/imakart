#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "GraphicEngine.hpp"
#include "GameEngine.hpp"
#include "ContextManager.hpp"

class Application
{
public:
  Application();

  sf::RenderWindow& setupEverything();
  void startGame(sf::RenderWindow& window);

private:
  bool handleEvents(sf::RenderWindow& window);

  GameEngine gameEngine;
  GraphicEngine graphicEngine;
  ContextManager contextManager;
};

#endif // APPLICATION_HPP
