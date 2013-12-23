#include "Scenario_obs.hpp"

Scenario_obs::Scenario_obs()
{
  mapStates["graphicReady"] = graphicEngineReady;
  mapStates["sleep"] = sleep;
  state = "sleep";
  loadIterations = 0;
  isGraphicReady = false;
}

Scenario_obs::~Scenario_obs(){
  gameE = nullptr;
  graphicE= nullptr;
  mapStates.erase(mapStates.begin(), mapStates.end());
}

void Scenario_obs::update(std::string notification){

  switch(mapStates[notification]){

    case graphicEngineReady:{
        if(loadIterations != 2){ //On attend deux tours de boucle du graphicEngine IN_RACE avant de reset le chrono
          state=notification;
          gameE->getChrono().init();
          loadIterations++;
        }else{
          isGraphicReady = true;
        }
      break;
    }
    case countdown:{
      break;
    }
    case sleep:{
      break;
    }
  }

}
