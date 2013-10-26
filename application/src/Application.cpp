#include "Application.hpp"
#include "SDL/SDL.h"
#include "GameEngine.hpp"
#include "EventHandler.hpp"

Application::Application(GameEngine& gameEngine)
  : gameEngine(gameEngine) {}

void Application::setupEverything()
{
  gameEngine.init();

}

void Application::startGame()
{
  bool askedForQuit = false;
  do
  {
    graphicEngine.renderFrame();
    gameEngine.update();
    askedForQuit = handleEvents();
  } while (!askedForQuit);
}

bool Application::handleEvents()
{
  const EventHandler& handler = gameEngine.getHandler();

  SDL_Event e;
  while(SDL_PollEvent(&e)) {

    if (e.type == SDL_QUIT)
      return true;

    if (e.type != SDL_KEYDOWN || e.type != SDL_KEYUP)
      continue;

    switch(e.key.keysym.sym) {
      case SDLK_DOWN:
        handler.down();
      break;

      case SDLK_UP:
        handler.up();
      break;
      default:
      break;

    }
  }
  return false;
}
