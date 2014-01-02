#include "ContextManager.hpp"
#include "GameEngine.hpp"
#include "GraphicEngine.hpp"
#include "Menu2D.hpp"
#include "ChronoTexte.hpp"
#include "KartCube.hpp"
#include "Skybox.hpp"
#include "Cube.hpp"
#include "Hangar.hpp"
#include "Light.hpp"
#include "Kart.hpp"
#include "Map3D.hpp"
#include "Mesh.hpp"
#include <iostream>
#include <stdexcept>
#include "Camera.hpp"
#include "Interface.hpp"
#include "World3D.hpp"
#include "SpeedTexte.hpp"
#include "convert.hpp"
#include "ItemGraphic2D.hpp"
#include "ItemInterface.hpp"

ContextManager::ContextManager(GameEngine& gameEngine, GraphicEngine& graphicEngine)
  : gameEngine(gameEngine), graphicEngine(graphicEngine), raceEventHandler(gameEngine, graphicEngine),
    menuEventHandler(gameEngine, graphicEngine), lastGameState(NO_STATE)
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

  else if (currentGameSate == IN_MENU_OPTIONS)
    setupMenuOptionsContext();

  else if (currentGameSate == IN_MENU_KART)
    setupMenuKartContext();

  else if (currentGameSate == IN_MENU_MAP)
    setupMenuMapContext();

  else if (currentGameSate == IN_RACE)
    setupRaceContext();

  else if (currentGameSate == IN_RACE_MENU)
    setupRaceMenuContext();

  lastGameState = currentGameSate;

  //Ajouter gestion du menu en course
}

void ContextManager::setupMenuContext() const
{
  graphicEngine.reset();
  Menu2D* menu2D = Menu2D::initialiseMainMenu();
  MenuLogic* menuLogic = MenuLogic::initialiseMainMenu();
  Interface* interfaceMenu = new Interface();
  for (unsigned int i = 0; i < menu2D->nbButtonInMenu; ++i){
    menu2D->getTab2DMenu(i)->setModelToRepresent( *(menuLogic->getTabInterfaceElement(i)) );
  }

  gameEngine.setMenu(menuLogic);
  menu2D->setModelToRepresent(gameEngine.getMenuLogic());
  interfaceMenu->addObject2D(menu2D);

  graphicEngine.setCurrentInterface(interfaceMenu);

  World3D* menuWorld = new World3D(graphicEngine.getSettings().WINDOW_WIDTH, graphicEngine.getSettings().WINDOW_HEIGHT);//Vide
  graphicEngine.setCurrentWorld3D(menuWorld);
}

void ContextManager::setupMenuOptionsContext() const
{
  graphicEngine.reset();
  Menu2D* menu2D = Menu2D::initialiseOptionsMenu();
  MenuLogic* menuLogic = MenuLogic::initialiseOptionsMenu();
  Interface* interfaceMenu = new Interface();
  for (unsigned int i = 0; i < menu2D->nbButtonInMenu; ++i){
    menu2D->getTab2DMenu(i)->setModelToRepresent( *(menuLogic->getTabInterfaceElement(i)) );
  }

  gameEngine.setMenu(menuLogic);
  menu2D->setModelToRepresent(gameEngine.getMenuLogic());
  interfaceMenu->addObject2D(menu2D);

  graphicEngine.setCurrentInterface(interfaceMenu);

  World3D* menuWorld = new World3D(graphicEngine.getSettings().WINDOW_WIDTH, graphicEngine.getSettings().WINDOW_HEIGHT);//Vide
  graphicEngine.setCurrentWorld3D(menuWorld);
}

void ContextManager::setupMenuKartContext() const
{
  graphicEngine.reset();
  Menu2D* menu2D = Menu2D::initialiseKartMenu(Hangar::getSingletonHangar()->getKartsName());
  MenuLogic* menuLogic = MenuLogic::initialiseKartMenu(Hangar::getSingletonHangar()->getKartsName());

  Interface* menuInterface = new Interface();
  for (unsigned int i = 0; i < menu2D->nbButtonInMenu; ++i){
    menu2D->getTab2DMenu(i)->setModelToRepresent( *(menuLogic->getTabInterfaceElement(i)) );

    for(unsigned int j = 0; j<menu2D->getTab2DMenu(i)->getOwnershipOnGeneratedText().size(); ++j){
      menuInterface->addObjectTexte((menu2D->getTab2DMenu(i)->getOwnershipOnGeneratedText())[j]);
    }
  }
  gameEngine.setMenu(menuLogic);
  menu2D->setModelToRepresent(gameEngine.getMenuLogic());

  menuInterface->addObject2D(menu2D);
  graphicEngine.setCurrentInterface(menuInterface);

  World3D* menuWorld = new World3D(graphicEngine.getSettings().WINDOW_WIDTH, graphicEngine.getSettings().WINDOW_HEIGHT);//Vide
  graphicEngine.setCurrentWorld3D(menuWorld);
}

void ContextManager::setupMenuMapContext() const
{
  graphicEngine.reset();
  Menu2D* menu2D = Menu2D::initialiseMapMenu();
  MenuLogic* menuLogic = MenuLogic::initialiseMapMenu();

  Interface* menuInterface = new Interface();
  for (unsigned int i = 0; i < menu2D->nbButtonInMenu; ++i){
    menu2D->getTab2DMenu(i)->setModelToRepresent( *(menuLogic->getTabInterfaceElement(i)) );
  }

  gameEngine.setMenu(menuLogic);
  menu2D->setModelToRepresent(gameEngine.getMenuLogic());

  menuInterface->addObject2D(menu2D);
  graphicEngine.setCurrentInterface(menuInterface);

  World3D* menuWorld = new World3D(graphicEngine.getSettings().WINDOW_WIDTH, graphicEngine.getSettings().WINDOW_HEIGHT);//Vide
  graphicEngine.setCurrentWorld3D(menuWorld);
}

void ContextManager::setupRaceContext() const
{
if(!gameEngine.inPause()){
  graphicEngine.reset();

  PointLight* light = new PointLight();
  PointLight* l = new PointLight(glm::vec3(50.f,30.f,50.f));
  //light->linkToPositionable(gameEngine.getPlayerKart());

  //-------------Chargement relatifs a la map
  Map* map = new Map();
  //Plus tard à remplacer par le choix dans le menu
  try
  {
    map->loadFromFile("maps/plage.txt");
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
    mapMesh->loadFromFile("data/plage.dae");
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

  //L'engine devient le propriÃ©taire de la camera et prend en charge sa destruction
  const GraphicSettings& settings = graphicEngine.getSettings();
  Camera* camera = new Camera(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT);
  camera->linkToPositionable(gameEngine.getPlayerKart());

  World3D* gameWorld = new World3D(graphicEngine.getSettings().WINDOW_WIDTH, graphicEngine.getSettings().WINDOW_HEIGHT);
  gameWorld->setCamera(camera);
  gameWorld->addLight(light);
  gameWorld->addLight(l);
  gameWorld->addObject3D(minionMesh);
  gameWorld->addObject3D(mapMesh);
 
  //pour voir les bounding boxes sous forme de cube
  /*for (auto it = map->getBoudingBoxes().begin(); it != map->getBoudingBoxes().end(); ++it)
  {
    KartCube* visibleBB = new KartCube();
    visibleBB->setSize(it->getSize());
    visibleBB->setModelToRepresent(*it);
    gameWorld->addObject3D(visibleBB);
  }*/

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
  gameWorld->addObject3D(opponentMesh);
  gameEngine.getOpponent(0).startMovement();

  //Init de l'interface
  Interface* gameInterface = new Interface();
  ChronoTexte* chrono = new ChronoTexte();
  chrono->setModelToRepresent(gameEngine.getChrono());
  chrono->setPosition(10, 570, 20);
  gameInterface->addObjectTexte(chrono);

  //Récupérer le speed du kart
  SpeedTexte* currentSpeedKart = new SpeedTexte(gameEngine.getPlayerKart().getCurrentSpeed());
  gameInterface->addObjectTexte(currentSpeedKart);

  //Afficher un objet mode degeu :D
  ItemGraphic2D* playerItem2D = new ItemGraphic2D(0.7,0.7,0.2,0.2,"textures/items/banane.png");
  InterfaceElement* item = ItemInterface::getSingletonItemInterface();
  playerItem2D->setModelToRepresent(*item);
  gameInterface->addObject2D(playerItem2D);

  graphicEngine.setCurrentInterface(gameInterface);
  graphicEngine.setCurrentWorld3D(gameWorld);
}else{
  Interface* gameInterface = graphicEngine.getInterface();
  //Supprime le menu de pause
  gameInterface->deleteLastObject2D();
  gameEngine.switchPause();
}
 
}

void ContextManager::setupRaceMenuContext() const{
  Interface* gameInterface = graphicEngine.getInterface();

  Menu2D* menu2D = Menu2D::initialiseRaceMenu();
  MenuLogic* menuLogic = MenuLogic::initialiseRaceMenu();

  for (unsigned int i = 0; i < menu2D->nbButtonInMenu; ++i){
    menu2D->getTab2DMenu(i)->setModelToRepresent( *(menuLogic->getTabInterfaceElement(i)) );
  }

  gameEngine.setMenu(menuLogic);
  menu2D->setModelToRepresent(gameEngine.getMenuLogic());
  gameInterface->addObject2D(menu2D);
}

const EventHandler& ContextManager::getHandler() const
{
  if (gameEngine.getState() == IN_MENU || gameEngine.getState() == IN_MENU_MAP || gameEngine.getState() == IN_MENU_KART || gameEngine.getState() == IN_RACE_MENU){
    return menuEventHandler;
  }else if (gameEngine.getState() == IN_RACE){
    return raceEventHandler;
  }
  return menuEventHandler;//TODO
}
