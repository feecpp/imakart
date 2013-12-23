#include "Application.hpp"
#include <SFML/Graphics.hpp>
#include "EventHandler.hpp"
#include <iostream>

Application::Application()
  : contextManager(gameEngine, graphicEngine)
{
  scenario = new Scenario_obs();
  gameEngine.attach(scenario);
  graphicEngine.attach(scenario);

  //L'observateur n'est pas passif il doit les connaitre pour leur donner des ordres.
  scenario->gameE = &gameEngine;
  scenario->graphicE = &graphicEngine;
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

void Application::handleEvents(sf::RenderWindow& window)
{
  const EventHandler& handler = contextManager.getHandler();	 

  bool inRace = gameEngine.getState() == IN_RACE;

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
            if (e.key.code == sf::Keyboard::Down && !inRace)
              handler.pressDown();

            else if (e.key.code == sf::Keyboard::Up && !inRace)
              handler.pressUp();

            else if (e.key.code == sf::Keyboard::Left && !inRace)
              handler.pressLeft();

            else if (e.key.code == sf::Keyboard::Right && !inRace)
              handler.pressRight();

            else if (e.key.code == sf::Keyboard::Return)
              handler.pressEnter();

            else if (e.key.code == sf::Keyboard::Space && !inRace)
              handler.pressSpace();

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

            else if (e.key.code == sf::Keyboard::Space)
              handler.releaseSpace();

            break;

        default:
          break;
      }
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && inRace){
    handler.pressUp();
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && inRace){
    handler.pressDown();
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && inRace){
    handler.pressLeft();
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && inRace){
    handler.pressRight();
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && inRace){
    handler.pressSpace();
  }

}
