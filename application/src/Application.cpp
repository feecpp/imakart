#include "Application.hpp"
#include "SDL/SDL.h"
#include "EventHandler.hpp"
#include "Kart.hpp"
#include <iostream>

Application::Application()
   {}

void Application::setupEverything()
{
  graphicEngine.init();
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

    graphicEngine.swapBuffers();
  } while (!askedForQuit);
}

bool Application::handleEvents()
{
  const EventHandler& handler = gameEngine.getHandler();

  SDL_Event e;
  while(SDL_PollEvent(&e)) {

    if (e.type == SDL_QUIT)
      return true;

    if (e.type != SDL_KEYDOWN && e.type != SDL_KEYUP)
      continue;

    switch(e.key.keysym.sym) {
      case SDLK_DOWN:
        handler.down();
      break;
      case SDLK_UP:
        handler.up();
      break;
      case SDLK_LEFT:
          handler.left();
        break;
      case SDLK_RIGHT:
        handler.right();
        break;
      default:
      break;

    }
  }
  return false;
}
