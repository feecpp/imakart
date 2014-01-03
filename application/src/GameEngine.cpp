#include "GameEngine.hpp"
#include "Kart.hpp"
#include "ItemLogic.hpp"
#include <iostream>

GameEngine::GameEngine()
  : state (IN_MENU), player(nullptr), currentMap(nullptr), chrono(nullptr), exitFlag(false), pause(false), buffer(0.f), lag(0.f), lastSecond(3), counterStarted(false), finishTimerStarted(false)

{
  chrono = new ChronoLogic();
  setupOpponents(1);
}

GameEngine::~GameEngine()
{
  delete player;
  delete currentMap;
  delete chrono;

  for (unsigned int i = 0; i < opponents.size(); ++i)
  {
    delete opponents[i];
  }
}

void GameEngine::init()
{
  clock.restart();
}

void GameEngine::update()
{
  if(!pause)
  {
    float elapsedTime = clock.restart().asMilliseconds();
    lag += elapsedTime;

  //Gestion du compte à rebour du début de course
  //C'est pas propre, dès que j'ai le temps (si j'en ai) je nettoie
  if (state == BEFORE_RACE_BEGIN)
  {
    if (!counterStarted)
    {
      counter.restart();
      counterStarted = true;
    }

    if (counter.getElapsedTime().asSeconds() >= 2 && lastSecond <= 0)
    {
      GameEventData data;
      data.lastSecond = lastSecond;
      eventStack.push(GameEvent(RACE_BEGIN, data));
      state = IN_RACE;
      counterStarted = false;
    }

    if (counter.getElapsedTime().asSeconds() >= 2 && lastSecond > 0)
    {
      GameEventData data;
      data.lastSecond = lastSecond;
      eventStack.push(GameEvent(COUNTER_UPDATE, data));
      counter.restart();
      lastSecond--;
    }
  }

  //Mettre à jour les objets de la simulation ici (en fonction du temps)
  //Cette partie a vraiment besoin qu'on réfléchisse sur l'archi du Game Engine!
    while (lag >= TURN_DURATION_IN_MILLIS)
    {
      if(state != IN_RACE)
      {
        chrono->update(0.f);
      }
      else
      {
        //Uniformiser la gestion du temps
        getPlayerKart().update(TURN_DURATION_IN_MILLIS / 1000.f);
        getOpponentKart(0).update(TURN_DURATION_IN_MILLIS / 1000.f);
        chrono->update(TURN_DURATION_IN_MILLIS / 1000.f);
        //Premiere gestion ultra basique de la physique des collisions
        doPhysic();

        auto itemsOnMap = currentMap->getItemsGenerators();
        for (auto it = itemsOnMap.begin(); it != itemsOnMap.end(); ++it)
        {
          if (getPlayerKart().getBoundingBox().collideWith(it->getBoundingBox()) && !getPlayer().hasItem())
          {
            getPlayer().setItem(it->getRandomItem());
          }
        }

        player->validateCheckpoints();
      }

      lag -= TURN_DURATION_IN_MILLIS;
    }
  }
  else
  {
    clock.restart();
  }

  //LALALA JE SUIS SALE : code de fin de jeu
  if (state == END_OF_RACE)
  {
    if (!finishTimerStarted)
    {
      finishTimer.restart();
      finishTimerStarted = true;
    }
    //On réinitialise tout
    if (finishTimer.getElapsedTime().asSeconds() > 5)
    {
      state = IN_MENU;
      finishTimerStarted = false;
      counterStarted = false;
      lastSecond = 3;
    }
  }
}

void GameEngine::switchPause()
{
  //Si on sort de la pause pendant le chrono
  if (state == BEFORE_RACE_BEGIN && pause)
    counter.restart();

  pause = !pause;

}

void GameEngine::activateExitFlag()
{
  exitFlag = true;
}

void GameEngine::deactivateExitFlag()
{
  exitFlag = false;
}

bool GameEngine::getExitFlag() const
{
  return exitFlag;
}

void GameEngine::setupPlayer(const std::string& playerKartName)
{
  player = new Player(Hangar::getSingletonHangar()->createKartInstanceByName(playerKartName), eventStack);
}

void GameEngine::setupOpponents(unsigned int nbOpponents)
{
  for (unsigned int i=0; i<nbOpponents; ++i){
    //Pour ceux qui se demanderait, le hangar se crée a ce moment, c'est a dire au lancement du jeu
    opponents.push_back(new Opponent(Hangar::getSingletonHangar()->createKartInstanceByName("Licorne")));
  }
}

Player& GameEngine::getPlayer() const
{
  //Pas mal de taff encore sur la gestion propre de la création du Player, des Karts...
  assert(player != nullptr);
  return *player;
}


Opponent& GameEngine::getOpponent(unsigned int id) const
{
  //Pas mal de taff encore sur la gestion propre de la création du Player, des Karts...
  assert(opponents[id] != nullptr);
  return *(opponents[id]);
}

Kart& GameEngine::getPlayerKart() const
{
  assert(player != nullptr);
  return player->getKart();
}

Kart& GameEngine::getOpponentKart(unsigned int id) const
{
  assert(opponents[id] != nullptr);
  return opponents[id]->getKart();
}

void GameEngine::setCurrentMap(Map* newMap)
{
  delete currentMap;
  currentMap = nullptr;
  currentMap = newMap;
}

Map& GameEngine::getCurrentMap() const
{
  assert(currentMap != nullptr);
  return *currentMap;
}

ChronoLogic& GameEngine::getChrono() const
{
  assert(chrono != nullptr);
  return *chrono;
}

void GameEngine::doPhysic()
{
  assert(currentMap != nullptr);
  //Securite
  auto boundingBoxes = currentMap->getBoudingBoxes();
  for (auto it = boundingBoxes.begin(); it != boundingBoxes.end(); ++it)
  {
    //Oui, c'est sale
    if (getPlayerKart().getBoundingBox().collideWith(*it))
    {
      getPlayerKart().bounce();
    }
  }
}
