#include "Application.hpp"
#include "SDL/SDL.h"
#include "EventHandler.hpp"
#include "Kart.hpp"
#include "KartCube.hpp"
#include "Menu2D.hpp"
#include "MenuLogic.hpp"
#include <iostream>

Application::Application()
  : contextManager(gameEngine, graphicEngine)
   {}

void Application::setupEverything()
{
  graphicEngine.init();
  gameEngine.init();

  contextManager.updateContextIfNeeded();
}

void Application::startGame()
{
  bool askedForQuit = false;
  do
  {
    graphicEngine.renderFrame();
    gameEngine.update();
    askedForQuit = handleEvents();
    contextManager.updateContextIfNeeded();

    graphicEngine.swapBuffers();
  } while (!askedForQuit);
}

bool Application::handleEvents()
{
  const EventHandler& handler = contextManager.getHandler();
		 
  SDL_Event e;
  while(SDL_PollEvent(&e)) {

    if (e.type == SDL_QUIT)
      return true;

    switch(e.type) {

      case SDL_KEYDOWN :

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
  }
  return false;
}
