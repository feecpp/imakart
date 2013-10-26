#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "WorldRepresentation.hpp"

class Game;

class GameController
{
public:
  GameController(Game& game);

  void setupEverything();
  void startGame();

  bool handleEvents();

private:
  Game& game;
  WorldRepresentation worldRepresentation;
};

#endif // GAME_CONTROLLER_HPP
