#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "GraphicEngine.hpp"
#include "GameEngine.hpp"
#include "ContextManager.hpp"
#include "Scenario_obs.hpp"

class Application
{
public:
  Application();

  sf::RenderWindow& setupEverything();
  void startGame(sf::RenderWindow& window);

private:
  void handleEvents(sf::RenderWindow& window);

  GameEngine gameEngine;
  GraphicEngine graphicEngine;
  ContextManager contextManager;
  Scenario_obs* scenario;
};

#endif // APPLICATION_HPP
