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

  //Fonction temporaire pour ne pas avoir
  //besoin de passer par le menu tant qu'il n'est pas pret
  //A appeler dans le main à la place de setupEverything() et startGame()
  void testRace();

private:
  void handleEvents(sf::RenderWindow& window);

  GameEngine gameEngine;
  GraphicEngine graphicEngine;
  ContextManager contextManager;
};

#endif // APPLICATION_HPP
