#include "Application.hpp"
#include "SDL/SDL.h"
#include "EventHandler.hpp"
#include "Kart.hpp"
#include "KartCube.hpp"
#include "Menu2D.hpp"
#include "MenuLogic.hpp"
#include <iostream>

Application::Application()
   {}

void Application::setupEverything()
{
  graphicEngine.init();
  gameEngine.init();

  KartCube* cube = new KartCube();
  cube->setModelToRepresent(gameEngine.getPlayer().getKart());
  graphicEngine.addObject3D(cube);

  Menu2D* menu = new Menu2D();
  MenuLogic* menuLogic = new MenuLogic();
  menu->initialiseMainMenu();
  menuLogic->initialiseMainMenu();
  gameEngine.setMenu(menuLogic);
  menu->setModelToRepresent(gameEngine.getMenuLogic());
  graphicEngine.addObject2D(menu);
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
	
/* Agis a la fois a l'appuis mais au relachement de la touche pas optimisé pour le menu 
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
*/
  }
  return false;
}
