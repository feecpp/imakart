#include "ContextManager.hpp"
#include "GameEngine.hpp"
#include "GraphicEngine.hpp"
#include "Menu2D.hpp"
#include "ChronoTexte.hpp"
#include "KartCube.hpp"
#include "Skybox.hpp"
#include "Cube.hpp"
#include "Light.hpp"
#include "Kart.hpp"
#include "Map3D.hpp"
#include "Mesh.hpp"
#include <iostream>
#include <stdexcept>
#include "Camera.hpp"

ContextManager::ContextManager(GameEngine& gameEngine, GraphicEngine& graphicEngine)
  : gameEngine(gameEngine), graphicEngine(graphicEngine), raceEventHandler(gameEngine, graphicEngine),
    menuEventHandler(gameEngine), lastGameState(NO_STATE)
{
}

void ContextManager::updateContextIfNeeded()
{
  GameState currentGameSate = gameEngine.getState();

  //Rien Ã  faire dans ce cas
  if (lastGameState == currentGameSate)
    return;

  if (currentGameSate == IN_MENU)
    setupMenuContext();

  else if (currentGameSate == IN_MENU_KART)
    setupMenuKartContext();

  else if (currentGameSate == IN_MENU_MAP)
    setupMenuMapContext();

  else if (currentGameSate == IN_RACE)
    setupRaceContext();

  lastGameState = currentGameSate;

  //Ajouter gestion du menu en course
}

void ContextManager::setupMenuContext() const
{
  graphicEngine.reset();
  graphicEngine.useMenuProgram();
  Menu2D* menu2D = Menu2D::initialiseMainMenu();
  MenuLogic* menuLogic = MenuLogic::initialiseMainMenu();

  for (unsigned int i = 0; i < menu2D->nbButtonInMenu; ++i){
    menu2D->getTab2DMenu(i)->setModelToRepresent( *(menuLogic->getTabInterfaceElement(i)) );
  }

  gameEngine.setMenu(menuLogic);
  menu2D->setModelToRepresent(gameEngine.getMenuLogic());
  graphicEngine.addObject2D(menu2D);
}

void ContextManager::setupMenuKartContext() const
{
  graphicEngine.reset();
  graphicEngine.useMenuProgram();


  Menu2D* menu2D = Menu2D::initialiseKartMenu(gameEngine.getHangar().getKartsName());
  MenuLogic* menuLogic = MenuLogic::initialiseKartMenu(gameEngine.getHangar().getKartsName());

  for (unsigned int i = 0; i < menu2D->nbButtonInMenu; ++i){
    menu2D->getTab2DMenu(i)->setModelToRepresent( *(menuLogic->getTabInterfaceElement(i)) );
    graphicEngine.addObjectTexte(menu2D->getTab2DMenu(i)->getObjTexte2D());
  }

  gameEngine.setMenu(menuLogic);
  menu2D->setModelToRepresent(gameEngine.getMenuLogic());
  graphicEngine.addObject2D(menu2D);
}

void ContextManager::setupMenuMapContext() const
{
  graphicEngine.reset();
  graphicEngine.useMenuProgram();
  Menu2D* menu2D = Menu2D::initialiseMapMenu();
  MenuLogic* menuLogic = MenuLogic::initialiseMapMenu();

  for (unsigned int i = 0; i < menu2D->nbButtonInMenu; ++i){
    menu2D->getTab2DMenu(i)->setModelToRepresent( *(menuLogic->getTabInterfaceElement(i)) );
  }

  gameEngine.setMenu(menuLogic);
  menu2D->setModelToRepresent(gameEngine.getMenuLogic());
  graphicEngine.addObject2D(menu2D);
}

void ContextManager::setupRaceContext() const
{
  graphicEngine.reset();
  graphicEngine.useRaceProgram();

  const GraphicSettings& settings = graphicEngine.getSettings();
  Camera* camera = new Camera(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT);
  camera->linkToPositionable(gameEngine.getPlayerKart());

  Light* light = new Light();
  light->linkToPositionable(gameEngine.getPlayerKart());

  //Gérer plusieurs lumières ponctuelles
  Light* lightpon1 = new Light(glm::vec3(30.f,0.f,5.f));
  Light* lightpon2 = new Light(glm::vec3(0.f,0.f,0.f));
  Light* lightpon3 = new Light(glm::vec3(0.f,0.f,-10.f));

  //-------------Chargement relatifs a la map
  Map* map = new Map();
  //Plus tard à remplacer par le choix dans le menu
  try
  {
    map->loadFromFile("maps/Imakart_Map_test.txt");
  }
  catch(std::runtime_error er)
  {
    std::cerr << er.what() << std::endl;
    gameEngine.activateExitFlag();
  }
  gameEngine.setCurrentMap(map);


  Mesh* mapMesh = new Mesh();
  try
  {
    mapMesh->loadFromFile("data/Imakart_Map_test.dae");
  }
  catch(std::runtime_error er)
  {
    std::cerr << er.what() << std::endl;
    gameEngine.activateExitFlag();
  }
  mapMesh->setModelToRepresent(*map);


  //---------Chargements relatifs au Kart
  Mesh* minionMesh = new Mesh();
  try
  {
    minionMesh->loadFromFile("data/"+ gameEngine.getPlayerKart().getName() + ".dae");
  }catch(std::runtime_error er)
  {
    std::cerr << er.what() << std::endl;
    gameEngine.activateExitFlag();
  }
  minionMesh->setModelToRepresent(gameEngine.getPlayerKart());

  //L'engine devient le propriÃ©taire de la camÃ©ra et prend en charge sa destruction
  graphicEngine.setCamera(camera);
  graphicEngine.addLight(light);
  //graphicEngine.addLight(lightpon1);
  //graphicEngine.addLight(lightpon2);
  //graphicEngine.addLight(lightpon3);
  graphicEngine.addObject3D(minionMesh);
  graphicEngine.addObject3D(mapMesh);
  graphicEngine.getSkybox()->setCamera(camera);

  //pour voir les bounding boxes sous forme de cube
  for (auto it = map->getBoudingBoxes().begin(); it != map->getBoudingBoxes().end(); ++it)
  {
    KartCube* visibleBB = new KartCube();
    visibleBB->setSize(it->getSize());
    visibleBB->setModelToRepresent(*it);
    graphicEngine.addObject3D(visibleBB);
  }

  //Dessin d'un adversaire
  Mesh* opponentMesh = new Mesh();
  try
  {
    opponentMesh->loadFromFile("data/"+ gameEngine.getOpponentKart(0).getName() + ".dae");
  }catch(std::runtime_error er)
  {
    std::cerr << er.what() << std::endl;
    gameEngine.activateExitFlag();
  }
  opponentMesh->setModelToRepresent(gameEngine.getOpponentKart(0));
  graphicEngine.addObject3D(opponentMesh);
  gameEngine.getOpponent(0).startMovement();

  ChronoTexte* chrono = new ChronoTexte();
  chrono->setModelToRepresent(gameEngine.getChrono());
  graphicEngine.addObjectTexte(chrono);

}

const EventHandler& ContextManager::getHandler() const
{
  if (gameEngine.getState() == IN_MENU || gameEngine.getState() == IN_MENU_MAP || gameEngine.getState() == IN_MENU_KART)
    return menuEventHandler;
  else if (gameEngine.getState() == IN_RACE)
    return raceEventHandler;
  return menuEventHandler;//TODO
}
