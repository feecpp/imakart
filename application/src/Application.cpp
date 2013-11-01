#include "Application.hpp"
#include <SFML/Graphics.hpp>
#include "EventHandler.hpp"
#include "Kart.hpp"
#include "KartCube.hpp"
#include "Menu2D.hpp"
#include "MenuLogic.hpp"
#include <iostream>

Application::Application()
  : contextManager(gameEngine, graphicEngine)
   {}

sf::RenderWindow& Application::setupEverything()
{
  sf::RenderWindow& window = graphicEngine.init();
  gameEngine.init();

  contextManager.updateContextIfNeeded();
  return window;
}

void Application::startGame(sf::RenderWindow& window)
{
  bool askedForQuit = false;
  do
  {
    graphicEngine.renderFrame();
    gameEngine.update();
    askedForQuit = handleEvents(window);
    contextManager.updateContextIfNeeded();

    graphicEngine.swapBuffers(window);
  } while (!askedForQuit);
}

bool Application::handleEvents(sf::RenderWindow& window)
{
  const EventHandler& handler = contextManager.getHandler();

  sf::Event e;
  while (window.pollEvent(e))
  {
      switch(e.type){
          case sf::Event::Closed :
                  window.close();
                  break;
          case sf::Event::KeyPressed:
              if (e.key.code == sf::Keyboard::Down){
                  handler.down();
              }
              if (e.key.code == sf::Keyboard::Up){
                  handler.up();
              }
              if (e.key.code == sf::Keyboard::Left){
                  handler.left();
              }
              if (e.key.code == sf::Keyboard::Right){
                  handler.right();
              }
              break;
      }

  }
  return false;
}
