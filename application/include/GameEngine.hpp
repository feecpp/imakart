#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include "GameEnumerations.hpp"
#include "RaceEventHandler.hpp"
#include "MenuEventHandler.hpp"
#include "Player.hpp"
#include "MenuLogic.hpp"
#include "Hangar.hpp"
#include "Map.hpp"
#include <SFML/System.hpp>
#include "ChronoLogic.hpp"
#include "Opponent.hpp"
#include "Observable.hpp"
#include <vector>
#include <stack>
#include "GameEvent.hpp"

/**
 * @brief Classe principale d'Imakart
 * Gère le déroulement du jeu. C'est le GameEngine
 * qui gère le temps dans la simulation.
 */
class GameEngine
{
public:
  GameEngine();
  ~GameEngine();

  void init();
  void update();

  std::stack<GameEvent>& getEvents()
    {return eventStack;}

  const GameState getState() const
    {return state;}

  void setState(GameState newState)
    {state = newState;}

  void setMenu(MenuLogic* menuToSet)
    {menu = *menuToSet;}

  void switchPause();

  void initNewRace();

  const bool inPause() const
    {return pause;}

  /**
   * @brief setExitFlag indique que le jeu va quitter
   * (la fonction getExitFlag() renvoie true)
   */
  void activateExitFlag();
  void deactivateExitFlag();
  bool getExitFlag() const;

  //Le player n'existe pas (=nullptr) tant que cette fonction n'est pas appelee
  void setupPlayer(const std::string& playerKartName);
  Player& getPlayer() const;

  Kart& getPlayerKart() const;

  //Création des adversaires
  void setupOpponents(unsigned int nbOpponents);
  Opponent& getOpponent(unsigned int id) const;
  Kart& getOpponentKart(unsigned int id) const;

  ///Le GameEngine devient responsable de la memoire liee a ce pointeur
  void setCurrentMap(Map* newMap);
  Map& getCurrentMap() const;

  ChronoLogic& getChrono() const;

  MenuLogic& getMenuLogic()
    {return menu;}

private:
  void doPhysic();
  static const char TURN_DURATION_IN_MILLIS = 20;

  GameState state;
  MenuLogic menu;
  std::stack<GameEvent> eventStack;

  Player* player;
  std::vector<Opponent*> opponents;
  Map* currentMap;
  sf::Clock clock;
  ChronoLogic* chrono;
  Observer* scenario;
  bool exitFlag;
  bool pause;
  float buffer;

  ///Pour la gestion du temps
  float lag;

  //Gestion compte à rebours du départ
  int lastSecond;
  sf::Clock counter;
  bool counterStarted;

  //Gestion de la fin
  sf::Clock finishTimer;
  bool finishTimerStarted;
};

#endif // GAMEENGINE_HPP
