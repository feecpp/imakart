#include "GameEngine.hpp"

GameEngine::GameEngine()
  : state (IN_MENU)
{
}

void GameEngine::init()
{

}

void GameEngine::update()
{
  player.getKart().update();
//    switch(player.getKart().getState()){
//        case MOVE_FORWARD:
//            player.getKart().moveForward();
//            break;
//        case MOVE_BACKWARD:
//            player.getKart().moveBackward();
//            break;
//        case TURN_LEFT:
//            player.getKart().turnLeft();
//             break;
//        case TURN_RIGHT:
//            player.getKart().turnRight();
//            break;
//        case REST_STATE:

//            break;
//    default:
//        break;
//    }
}

