#ifndef CONTEXTMANAGER_HPP
#define CONTEXTMANAGER_HPP

#include "RaceEventHandler.hpp"
#include "MenuEventHandler.hpp"
#include "GameEnumerations.hpp"

class GameEngine;
class GraphicEngine;


/*
 * Un contexte c'est un lien entre un modÃ¨le et sa vue.
 * En gros on veut une liste d'associations :
 * objet du game engine <==> objet du graphic engine
 */

/**
 * @brief The ContextManager class
 * se charge du sale boulot d'instancier tout ce qu'il faut et de dÃ©truire
 * tout ce qu'il faut Ã  chaque nouveau contexte, pour l'instant :
 * contexte race, contexte menu. Pour l'instant c'est fait Ã  la bourrin
 * mais voir la note du dessus sur ce qu'est un contexte et comment on pourrait
 * faire Ã§a de maniÃ¨re sexy aprÃ¨s.
 */
class ContextManager
{
public:

  ContextManager(GameEngine& gameEngine, GraphicEngine& graphicEngine);

  /**
   * @brief updateContextIfNeeded
   * VÃ©rifie si le contexte doit etre modifiÃ©
   * en se basant sur le state du GameEngine.
   */
  void updateContextIfNeeded();

  const EventHandler& getHandler() const;

private:
  void setupMenuContext() const;
  void setupMenuOptionsContext() const;
  void setupMenuKartContext() const;
  void setupMenuMapContext() const;
  void setupRaceContext() const;
  void setupRaceMenuContext() const;

  GameEngine& gameEngine;
  GraphicEngine& graphicEngine;
  RaceEventHandler raceEventHandler;
  MenuEventHandler menuEventHandler;
  GameState lastGameState;
};

#endif // CONTEXTMANAGER_HPP
