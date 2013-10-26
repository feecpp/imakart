#include "GameController.hpp"
#include "SDL/SDL.h"
#include "Game.hpp"
#include "EventHandler.hpp"

GameController::GameController(Game& game)
  : game(game) {}

void GameController::setupEverything()
{
  game.init();
}

void GameController::startGame()
{
  game.init();

  bool askedForQuit = false;
  do
  {
    worldRepresentation.show();
    game.update();
    askedForQuit = handleEvents();
  } while (!askedForQuit);
}

bool GameController::handleEvents()
{
  const EventHandler& handler = game.getHandler();

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
