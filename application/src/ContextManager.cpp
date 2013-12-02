#include "ContextManager.hpp"
#include "GameEngine.hpp"
#include "GraphicEngine.hpp"
#include "Menu2D.hpp"
#include "KartCube.hpp"
#include "Cube.hpp"
#include "Kart.hpp"
#include "Map3D.hpp"
#include "Mesh.hpp"
#include <iostream>

ContextManager::ContextManager(GameEngine& gameEngine, GraphicEngine& graphicEngine)
  : gameEngine(gameEngine), graphicEngine(graphicEngine), raceEventHandler(gameEngine, graphicEngine),
    menuEventHandler(gameEngine), lastGameState(NO_STATE)
{
}

void ContextManager::updateContextIfNeeded()
{
  GameState currentGameSate = gameEngine.getState();

  //Rien à faire dans ce cas
  if (lastGameState == currentGameSate)
    return;

  if (currentGameSate == IN_MENU)
    setupMenuContext();

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

void ContextManager::setupRaceContext() const
{
  graphicEngine.reset();
  graphicEngine.useRaceProgram();
  //KartCube* cube = new KartCube();
  //cube->setModelToRepresent(gameEngine.getPlayerKart());

  const GraphicSettings& settings = graphicEngine.getSettings();
  Camera* camera = new Camera(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT);
  camera->linkToPositionable(gameEngine.getPlayerKart());

 // Map3D* map = new Map3D();
  //map->setModelToRepresent(gameEngine.getMap());

  Mesh* testMesh = new Mesh();
  try
  {
    testMesh->loadFromFile("data/minionCouleur.obj");
  }catch(std::runtime_error er)
  {
    std::cerr << er.what() << std::endl;
    gameEngine.activateExitFlag();
  }
  testMesh->setModelToRepresent(gameEngine.getPlayerKart());
  //L'engine devient le propriétaire de la caméra et prend en charge sa destruction
  graphicEngine.setCamera(camera);
  //Le GraphicEngine devient également propriétaire des objets 3D qu'il contient
  //graphicEngine.addObject3D(cube);
  //graphicEngine.addObject3D(map);
  graphicEngine.addObject3D(testMesh);
}

const EventHandler& ContextManager::getHandler() const
{
  if (gameEngine.getState() == IN_MENU)
    return menuEventHandler;
  else if (gameEngine.getState() == IN_RACE)
    return raceEventHandler;
  return menuEventHandler;//TODO
}
