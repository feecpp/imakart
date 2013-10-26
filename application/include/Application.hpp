#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Game.hpp"
#include "GameController.hpp"

class Application
{
  void exec()
  {
    Game game;
    GameController controller(game);

    controller.setupEverything();
    controller.startGame();

  }
};

#endif // APPLICATION_HPP
