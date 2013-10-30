#ifndef CONTEXTMANAGER_HPP
#define CONTEXTMANAGER_HPP

#include "RaceEventHandler.hpp"
#include "MenuEventHandler.hpp"
#include "GameEnumerations.hpp"

class GameEngine;
class GraphicEngine;


/*
 * Un contexte c'est un lien entre un modèle et sa vue.
 * En gros on veut une liste d'associations :
 * objet du game engine <==> objet du graphic engine
 */

/**
 * Classe Singleton
 * @brief The ContextManager class
 * se charge du sale boulot d'instancier tout ce qu'il faut et de détruire
 * tout ce qu'il faut à chaque nouveau contexte, pour l'instant :
 * contexte race, contexte menu. Pour l'instant c'est fait à la bourrin
 * mais voir la note du dessus sur ce qu'est un contexte et comment on pourrait
 * faire ça de manière sexy après.
 */
class ContextManager
{
public:

  ContextManager(GameEngine& gameEngine, GraphicEngine& graphicEngine);

  /**
   * @brief updateContextIfNeeded
   * Vérifie si le contexte doit etre modifié
   * en se basant sur le state du GameEngine.
   */
  void updateContextIfNeeded();

  const EventHandler& getHandler() const;

private:
  void setupMenuContext() const;
  void setupRaceContext() const;

  GameEngine& gameEngine;
  GraphicEngine& graphicEngine;
  RaceEventHandler raceEventHandler;
  MenuEventHandler menuEventHandler;
  GameState lastGameState;
};

#endif // CONTEXTMANAGER_HPP
