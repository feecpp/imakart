#include "Application.hpp"
#include <SFML/Graphics.hpp>
#include "EventHandler.hpp"

Application::Application()
  : contextManager(gameEngine, graphicEngine)
{
}

sf::RenderWindow& Application::setupEverything()
{
  sf::RenderWindow& window = graphicEngine.init();
  gameEngine.init();

  contextManager.updateContextIfNeeded();
  return window;
}

void Application::startGame(sf::RenderWindow& window)
{

  do
  {
    graphicEngine.renderFrame();
    gameEngine.update();
    handleEvents(window);
    contextManager.updateContextIfNeeded();

    graphicEngine.swapBuffers();
  } while (!gameEngine.getExitFlag());
}

void Application::testRace()
{
  sf::RenderWindow& window = setupEverything();
  gameEngine.setState(IN_RACE);

  contextManager.updateContextIfNeeded();
  startGame(window);
}

void Application::handleEvents(sf::RenderWindow& window)
{
  const EventHandler& handler = contextManager.getHandler();	 

  sf::Event e;
  while (window.pollEvent(e))
  {
      switch(e.type)
      {
        case sf::Event::Closed :
                window.close();
                gameEngine.activateExitFlag();
        break;

        case sf::Event::KeyPressed:
            if (e.key.code == sf::Keyboard::Down)
                handler.pressDown();

            else if (e.key.code == sf::Keyboard::Up)
                handler.pressUp();

            else if (e.key.code == sf::Keyboard::Left)
                handler.pressLeft();

            else if (e.key.code == sf::Keyboard::Right)
                handler.pressRight();

            else if (e.key.code == sf::Keyboard::Return)
                return(handler.pressEnter());

            break;

        case sf::Event::KeyReleased:
            if (e.key.code == sf::Keyboard::Down)
                handler.releaseDown();

            else if (e.key.code == sf::Keyboard::Up)
                handler.releaseUp();

            else if (e.key.code == sf::Keyboard::Left)
                handler.releaseLeft();

            else if (e.key.code == sf::Keyboard::Right)
                handler.releaseRight();

            else if (e.key.code == sf::Keyboard::Return)
                handler.releaseEnter();

            break;

        default:
          break;
      }
  }
}
