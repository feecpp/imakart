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

void Application::testRace()
{
  setupEverything();
  gameEngine.setState(IN_RACE);

  contextManager.updateContextIfNeeded();
  startGame();
}

bool Application::handleEvents()
{
  const EventHandler& handler = contextManager.getHandler();
		 
  SDL_Event e;
  bool upup = true;
  bool downup = true;
  bool leftup = true;
  bool rightup = true;

  while(SDL_PollEvent(&e)) {

    switch(e.type) {
	
	  case SDL_QUIT : 
		return true;
		break;

      case SDL_KEYDOWN :

        switch(e.key.keysym.sym) {

		  case SDLK_RETURN:
			handler.enter();
		  break;
		  
          case SDLK_DOWN:
			downup = false;
            handler.down();
          break;

          case SDLK_UP:
			upup = false;
            handler.up();
          break;

          case SDLK_LEFT:
			leftup = false;
            handler.left();
          break;

          case SDLK_RIGHT:
			rightup = false;
            handler.right();
          break;

          default:
          break;
        }
        
        break;
        
      case SDL_KEYUP :
       
        switch(e.key.keysym.sym) {

          case SDLK_DOWN:
			downup = true;
          break;

          case SDLK_UP:
			upup = true;
          break;

          case SDLK_LEFT:
			leftup = true;
          break;

          case SDLK_RIGHT:
			rightup = true;
          break;

          default:
          break;
        }      
        
        break;
    }
  }
  
  if (!upup) //handler.up();
  if (!downup) //handler.down();// do smthing
  if (!leftup) //handler.left(); // do smthing
  if (!rightup){ }//handler.right(); // do smthing
 
  return false;
}
