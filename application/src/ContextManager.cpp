#include "ContextManager.hpp"
#include "GameEngine.hpp"
#include "GraphicEngine.hpp"
#include "Menu2D.hpp"
#include "ChronoTexte.hpp"
#include "KartCube.hpp"
#include "Skybox.hpp"
#include "Cube.hpp"
#include "Hangar.hpp"
#include "Kart.hpp"
#include "Map3D.hpp"
#include "Mesh.hpp"
#include <iostream>
#include <stdexcept>
#include "Camera.hpp"
#include "Interface.hpp"
#include "World3D.hpp"
#include "SpeedTexte.hpp"
#include "LapText.hpp"
#include "RankingText.hpp"
#include "convert.hpp"
#include "ItemGraphic2D.hpp"
#include "ItemInterface.hpp"
#include "ItemGenerator.hpp"
#include "ItemLogic.hpp"

#include <iostream>

ContextManager::ContextManager(GameEngine& gameEngine, GraphicEngine& graphicEngine)
  : gameEngine(gameEngine), graphicEngine(graphicEngine), raceEventHandler(gameEngine, graphicEngine),
    menuEventHandler(gameEngine, graphicEngine), lastGameState(NO_STATE)
{
}

void ContextManager::updateContextIfNeeded()
{
  GameState currentGameState = gameEngine.getState();

  if (lastGameState != currentGameState)
  {
    if (currentGameState == IN_MENU)
      setupMenuContext();

    else if (currentGameState == IN_MENU_OPTIONS)
      setupMenuOptionsContext();

    else if (currentGameState == IN_MENU_KART)
      setupMenuKartContext();

    else if (currentGameState == IN_MENU_MAP)
      setupMenuMapContext();

    else if (currentGameState == PREPARING_RACE)
      setupRaceContext();

    else if (currentGameState == IN_RACE_MENU)
      setupRaceMenuContext();

    else if (currentGameState == IN_RACE && lastGameState == IN_RACE_MENU)
    {
      Interface& gameInterface = graphicEngine.getCurrentInterface();
      //Supprime le menu de pause
      gameInterface.deleteLastObject2D();
      gameEngine.switchPause();
    }

    lastGameState = currentGameState;
  }

  std::stack<GameEvent>& eventStack = gameEngine.getEvents();
  //Pas très propre mais je sais pas encore comment détecter que le boost est fini

  while(!eventStack.empty())
  {
    GameEvent current = eventStack.top();
    eventStack.pop();
    Interface& interface = graphicEngine.getCurrentInterface();
    World3D& world3D = graphicEngine.getWorld3D();
    TimeLimitedText* splashText = nullptr;
    Mesh* itemGeneratorMesh = nullptr;

    switch(current.type)
    {
      case COUNTER_UPDATE:
        splashText = new TimeLimitedText(glimac::convertToString(current.data.lastSecond), 1000, glm::vec2(400,400), 50);
        interface.addTimeLimitedText(splashText);
        break;

      case RACE_BEGIN:
        splashText = new TimeLimitedText(std::string("GO !"), 1000, glm::vec2(400,400), 50);
        interface.addTimeLimitedText(splashText);
        break;

      case NEW_LAP:
        splashText = new TimeLimitedText(std::string("Tour " + glimac::convertToString(current.data.lapNumber)), 1000, glm::vec2(150,500), 50);
        interface.addTimeLimitedText(splashText);
        break;

      case RACE_FINISHED:
        splashText = new TimeLimitedText(std::string("Course terminee"), 1000, glm::vec2(150,500), 25);
        interface.addTimeLimitedText(splashText);
        gameEngine.setState(END_OF_RACE);
        break;

      case NEW_ITEM_ON_MAP:
        try
        {
          itemGeneratorMesh = new Mesh(graphicEngine.getMeshDataManager(), "data/itemGenerator.dae");
        }
        catch(std::runtime_error er)
        {
          std::cerr << er.what() << std::endl;
          delete itemGeneratorMesh;
          gameEngine.activateExitFlag();
        }
        gameEngine.setNewItemOnMap(current.data.itemLogicOnMap);

        itemGeneratorMesh->setModelToRepresent(*(current.data.itemLogicOnMap));
        world3D.addObject3D(itemGeneratorMesh);
        break;

      case USE_BOOST_BEGIN:
        graphicEngine.setMotionBlur(true);
        break;

      case USE_BOOST_END:
        graphicEngine.setMotionBlur(false);
        break;
    }
  }
  //Ajouter gestion du menu en course
}

void ContextManager::setupMenu(Menu2D* menu2D, MenuLogic* menuLogic, bool text) const
{
  graphicEngine.reset();

  Interface* interfaceMenu = new Interface();
  for (unsigned int i = 0; i < menu2D->nbButtonInMenu; ++i){
    menu2D->getTab2DMenu(i)->setModelToRepresent( *(menuLogic->getTabInterfaceElement(i)) );

    if(text)
    {
      for(unsigned int j = 0; j<menu2D->getTab2DMenu(i)->getOwnershipOnGeneratedText().size(); ++j){
        interfaceMenu->addObjectTexte((menu2D->getTab2DMenu(i)->getOwnershipOnGeneratedText())[j]);
      }
    }
  }

  gameEngine.setMenu(menuLogic);
  menu2D->setModelToRepresent(gameEngine.getMenuLogic());
  interfaceMenu->addObject2D(menu2D);

  graphicEngine.setCurrentInterface(interfaceMenu);

  World3D* menuWorld = new World3D(graphicEngine.getSettings().WINDOW_WIDTH, graphicEngine.getSettings().WINDOW_HEIGHT);//Vide
  graphicEngine.setCurrentWorld3D(menuWorld);
}

void ContextManager::setupMenuContext() const
{
  setupMenu(Menu2D::initialiseMainMenu(), MenuLogic::initialiseMainMenu(), false);
}

void ContextManager::setupMenuOptionsContext() const
{
  setupMenu(Menu2D::initialiseOptionsMenu(), MenuLogic::initialiseOptionsMenu(), false);
}

void ContextManager::setupMenuKartContext() const
{
  setupMenu(Menu2D::initialiseKartMenu(Hangar::getSingletonHangar()->getKartsName()), MenuLogic::initialiseKartMenu(Hangar::getSingletonHangar()->getKartsName()), true);
}

void ContextManager::setupMenuMapContext() const
{
  setupMenu(Menu2D::initialiseMapMenu(findMapFiles()), MenuLogic::initialiseMapMenu(findMapFiles()), true);
}

void ContextManager::setupRaceContext() const
{

  graphicEngine.reset();

  //Preload le mesh du launch item
  graphicEngine.getMeshDataManager().preloadMesh("data/itemGenerator.dae");

  PointLight* light = new PointLight();
  PointLight* l = new PointLight(glm::vec4(300.f,10.f,-100.f,1.0f));

  SpotLight* spot = new SpotLight();
  spot->linkToPositionable(gameEngine.getPlayerKart());

  //-------------Chargement relatifs a la map
  Map* map = new Map();
  std::string mapName = gameEngine.getSelectMapName();
  try
  {
    map->loadFromFile("maps/" + mapName + ".txt");
  }
  catch(std::runtime_error er)
  {
    std::cerr << er.what() << std::endl;
    gameEngine.activateExitFlag();
  }
  gameEngine.setCurrentMap(map);

  gameEngine.getPlayer().fillCheckpoints(map->getPlayerCheckpoints());
  gameEngine.getPlayer().fillOpponentCheckpoints(map->getOpponentCheckpoints());

  Mesh* mapMesh = nullptr;
  try
  {
    mapMesh = new Mesh(graphicEngine.getMeshDataManager(), "data/" + mapName + ".dae");
  }
  catch(std::runtime_error er)
  {
    std::cerr << er.what() << std::endl;
    gameEngine.activateExitFlag();
    delete mapMesh;
  }
  mapMesh->setModelToRepresent(*map);

  //---------Chargements relatifs au Kart
  Mesh* minionMesh = nullptr;
  try
  {
    minionMesh = new Mesh(graphicEngine.getMeshDataManager(), "data/"+ gameEngine.getPlayerKart().getName() + ".dae");
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
  //Un peu degeu car en dur
  if(mapName == "PlayaBanana")
  {
    gameWorld->setDay();
  }
  gameWorld->setCamera(camera);
  gameWorld->addLight(light);
  gameWorld->addLight(l);
  gameWorld->setSpot(spot);
  gameWorld->addObject3D(minionMesh);
  gameWorld->addObject3D(mapMesh);

  //Pour les itemGenerator
  auto itemsOnMap = map->getItemsGenerators();
  for (auto it = itemsOnMap.begin(); it != itemsOnMap.end(); ++it)
  {
    Mesh* itemGeneratorMesh = nullptr;
    try
    {
      itemGeneratorMesh = new Mesh(graphicEngine.getMeshDataManager(), "data/itemGenerator.dae");
    }
    catch(std::runtime_error er)
    {
      std::cerr << er.what() << std::endl;
      gameEngine.activateExitFlag();
      delete itemGeneratorMesh;
    }
    itemGeneratorMesh->setModelToRepresent(*(*it));
    gameWorld->addObject3D(itemGeneratorMesh);
  }

  //pour voir les bounding boxes sous forme de cube
  /*for (auto it = map->getBoudingBoxes().begin(); it != map->getBoudingBoxes().end(); ++it)
  {
    KartCube* visibleBB = new KartCube();
    visibleBB->setSize(it->getSize());
    std::cout << it->getSize()[0] << std::endl;
    visibleBB->setModelToRepresent(*it);
    gameWorld->addObject3D(visibleBB);
  }*/

  //Dessin d'un adversaire

  for(unsigned int i = 0; i< gameEngine.getOpponents().size();++i){
    gameEngine.getOpponent(i).fillCheckpoints(map->getOpponentCheckpoints());
    Mesh* opponentMesh = nullptr;
    try
    {
      opponentMesh = new Mesh(graphicEngine.getMeshDataManager(), "data/"+ gameEngine.getOpponentKart(i).getName() + ".dae");
    }catch(std::runtime_error er)
    {
      std::cerr << er.what() << std::endl;
      gameEngine.activateExitFlag();
      delete opponentMesh;
    }
    opponentMesh->setModelToRepresent(gameEngine.getOpponentKart(i));
    gameWorld->addObject3D(opponentMesh);
    gameEngine.getOpponent(i).startMovement();
  }

  //Init de l'interface
  Interface* gameInterface = new Interface();
  ChronoTexte* chrono = new ChronoTexte();
  chrono->setModelToRepresent(gameEngine.getChrono());
  chrono->setPosition(10, 570, 20);
  gameInterface->addObjectTexte(chrono);

  //Récupérer le speed du kart
  SpeedTexte* currentSpeedKart = new SpeedTexte(gameEngine.getPlayerKart().getCurrentSpeed());
  gameInterface->addObjectTexte(currentSpeedKart);

  //Récupérer le numero du tour
  LapText* currentLap = new LapText(gameEngine.getPlayer().getCurrentLap());
  gameInterface->addObjectTexte(currentLap);

  //Récupérer la position du joueur
  RankingText* currentRank = new RankingText(gameEngine.getPlayer().getRank());
  gameInterface->addObjectTexte(currentRank);

  //Afficher l'interface de l'item sans item selectionné
  ItemGraphic2D* playerItem2D = new ItemGraphic2D(0.7,0.7,0.2,0.2,"textures/items/noItem.png");
  InterfaceElement* item = ItemInterface::getSingletonItemInterface();
  playerItem2D->setModelToRepresent(*item);
  gameInterface->addObject2D(playerItem2D);

  graphicEngine.setCurrentInterface(gameInterface);
  graphicEngine.setCurrentWorld3D(gameWorld);
  gameEngine.setState(BEFORE_RACE_BEGIN);
}

void ContextManager::setupRaceMenuContext() const{
  Interface& gameInterface = graphicEngine.getCurrentInterface();

  Menu2D* menu2D = Menu2D::initialiseRaceMenu();
  MenuLogic* menuLogic = MenuLogic::initialiseRaceMenu();

  for (unsigned int i = 0; i < menu2D->nbButtonInMenu; ++i){
    menu2D->getTab2DMenu(i)->setModelToRepresent( *(menuLogic->getTabInterfaceElement(i)) );
  }

  gameEngine.setMenu(menuLogic);
  menu2D->setModelToRepresent(gameEngine.getMenuLogic());
  gameInterface.addObject2D(menu2D);
}

const EventHandler& ContextManager::getHandler() const
{
  if (gameEngine.getState() == IN_MENU || gameEngine.getState() == IN_MENU_MAP || gameEngine.getState() == IN_MENU_KART || gameEngine.getState() == IN_RACE_MENU){
    return menuEventHandler;
  }else if (gameEngine.getState() == IN_RACE || gameEngine.getState() == BEFORE_RACE_BEGIN){
    return raceEventHandler;
  }
  return menuEventHandler;//TODO
}
