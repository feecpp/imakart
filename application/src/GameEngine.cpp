#include "GameEngine.hpp"
#include "Kart.hpp"
#include "ItemLogic.hpp"
#include <iostream>
#include <fstream>
#include <dirent.h>
#ifndef WIN32
  #include <sys/types.h>
#endif


GameEngine::GameEngine()
  : state (IN_MENU), player(nullptr), currentMap(nullptr), chrono(nullptr), exitFlag(false), pause(false), buffer(0.f), lag(0.f), lastSecond(3), counterStarted(false), finishTimerStarted(false)

{
  chrono = new ChronoLogic();
  setupOpponents(3);
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

  for (unsigned int i = 0; i < itemsOnMap.size(); ++i)
  {
    delete itemsOnMap[i];
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
        for(unsigned int i =0; i<opponents.size(); ++i){
          getOpponentKart(i).update(TURN_DURATION_IN_MILLIS / 1000.f);
        }
        chrono->update(TURN_DURATION_IN_MILLIS / 1000.f);
        //Premiere gestion ultra basique de la physique des collisions
        doPhysic();

        auto itemsGeneratorsOnMap = currentMap->getItemsGenerators();
        for (auto it = itemsGeneratorsOnMap.begin(); it != itemsGeneratorsOnMap.end(); ++it)
        {
          if (getPlayerKart().getBoundingBox().collideWith((*it)->getBoundingBox()) && !getPlayer().hasItem())
          {
            getPlayer().setItem((*it)->getRandomItem());
            (*it)->setNotVisible();
          }
          (*it)->update();
        }

        //Gestion de la physique des items
        for (unsigned int i = 0; i < itemsOnMap.size(); ++i)
        {
          if(itemsOnMap[i] != nullptr){
            itemsOnMap[i]->updateLaunch();

            assert(currentMap != nullptr);

            auto boundingBoxes = currentMap->getBoudingBoxes();
            for (auto it = boundingBoxes.begin(); it != boundingBoxes.end(); ++it)
            {
              if (itemsOnMap[i]->getBoundingBox().collideWith(**it))
              {
                itemsOnMap[i]->colision();
              }
            }

            for(unsigned int j =0; j< opponents.size(); ++j)
            {
              if (itemsOnMap[i]->getBoundingBox().collideWith(opponents[j]->getKart().getBoundingBox()))
              {
                //Ajouter ici ce que dois faire l'opponent touché 
                opponents[i]->touched();
                itemsOnMap[i]->setNotVisible();
              }
            }
            if(!itemsOnMap[i]->isVisible())
            {
              itemsOnMap[i] = nullptr;
            }
		   }
        }

        player->validateCheckpoints();
        for(unsigned int i =0; i< opponents.size(); ++i){
          opponents[i]->validateCheckpoints();
        }

        //gestion du classement, assez sale, à améliorer
        player->setRank(1);

       for(unsigned int i =0; i< opponents.size(); ++i){
          if(player->getCurrentLap() < opponents[i]->getCurrentLap()){
            player->setRank(player->getRank()+1);
          }else if(player->getCurrentLap() == opponents[i]->getCurrentLap()){
            if(player->getNextCheck() < opponents[i]->getNextCheck()){
              player->setRank(player->getRank()+1);
            }else if (player->getNextCheck() == opponents[i]->getNextCheck()){
              if(player->getProgression() < opponents[i]->getProgression()){
                player->setRank(player->getRank()+1);
              }
            }
          }
        }
       //Fin de course
       for(unsigned int i =0; i< opponents.size(); ++i){
         if(opponents[i]->getCurrentLap() > Player::MAX_LAP){
           opponents[i]->endMovement();
         }
       }
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
  for (unsigned int i=1; i<=nbOpponents; ++i){
    //Pour ceux qui se demanderait, le hangar se crée a ce moment, c'est a dire au lancement du jeu
    if(i%3 == 1){
      opponents.push_back(new Opponent(Hangar::getSingletonHangar()->createKartInstanceByName("Rocket")));
      opponents[i-1]->getKart().setPosition(glm::vec3(9.f,0.f,-1.2f));
    }else if(i%3 == 2){
      opponents.push_back(new Opponent(Hangar::getSingletonHangar()->createKartInstanceByName("Licorne")));
      opponents[i-1]->getKart().setPosition(glm::vec3(1.9f,0.f,2.2f));
    }else if (i%3 == 0){
      opponents.push_back(new Opponent(Hangar::getSingletonHangar()->createKartInstanceByName("Jet")));
      opponents[i-1]->getKart().setPosition(glm::vec3(9.f,0.f,4.8f));
    }
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

void GameEngine::setNewItemOnMap(ItemLogic* newItem)
{
  itemsOnMap.insert(std::pair<int, ItemLogic*>(itemsOnMap.size(), newItem));
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

std::string GameEngine::getSelectMapName() const
{
  return selectMapName;
}

void GameEngine::setMapName(const std::string newMapName)
{
  selectMapName = newMapName;
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
    if (getPlayerKart().getBoundingBox().collideWith(**it))
    {
      getPlayerKart().bounce();
      return;
    }
  }

}


std::vector<std::string> findMapFiles()
{
    std::vector<std::string> fileNames;

    //Ouverture du répertoire des maps
    DIR* mapsDir = NULL;
    mapsDir = opendir("maps");
    if (mapsDir == NULL){
        std::cout << "Erreur - impossible d'accéder au répertoire des Maps" << std::endl;
    }

    //tous les fichiers du répertoire sont parcourus
    struct dirent* file = NULL;
    while ((file = readdir(mapsDir)) != NULL){

        std::string tmp = std::string(file->d_name); //nom + extension
        std::size_t found = tmp.find(".");
        std::string extension = tmp.substr (found+1);
        std::string name = tmp.substr (0,found);

        if(extension == "txt"){//L'extension va ptete changer
            fileNames.push_back(name);
        }
    }

    closedir(mapsDir);
    return fileNames;
}
