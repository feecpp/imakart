#include "Application.hpp"
#include <SFML/Graphics.hpp>
#include "EventHandler.hpp"

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

    graphicEngine.swapBuffers();
  } while (!askedForQuit);
}

void Application::testRace()
{
  sf::RenderWindow& window = setupEverything();
  gameEngine.setState(IN_RACE);

  contextManager.updateContextIfNeeded();
  startGame(window);
}

bool Application::handleEvents(sf::RenderWindow& window)
{
  const EventHandler& handler = contextManager.getHandler();	 

  sf::Event e;
  while (window.pollEvent(e))
  {
      switch(e.type)
      {
        case sf::Event::Closed :
                window.close();
                return true;
        break;
        case sf::Event::KeyPressed:
            if (e.key.code == sf::Keyboard::Down)
                handler.down();

            else if (e.key.code == sf::Keyboard::Up)
                handler.up();

            else if (e.key.code == sf::Keyboard::Left)
                handler.left();

            else if (e.key.code == sf::Keyboard::Right)
                handler.right();

            break;
        default:
          break;
      }
  }
  return false;
}
