#include "ContextManager.hpp"
#include "GameEngine.hpp"
#include "GraphicEngine.hpp"
#include "Menu2D.hpp"
#include "KartCube.hpp"
#include "Cube.hpp"

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
  KartCube* cube = new KartCube();
  cube->setModelToRepresent(gameEngine.getPlayer().getKart());

  const GraphicSettings& settings = graphicEngine.getSettings();
  Camera* camera = new Camera(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT);
  camera->linkToPositionable(gameEngine.getPlayer().getKart());

  //L'engine devient le propriétaire de la caméra et prend en charge sa destruction
  graphicEngine.setCamera(camera);
  graphicEngine.addObject3D(cube);
}

const EventHandler& ContextManager::getHandler() const
{
  if (gameEngine.getState() == IN_MENU)
    return menuEventHandler;
  else if (gameEngine.getState() == IN_RACE)
    return raceEventHandler;
  return menuEventHandler;//TODO
}
