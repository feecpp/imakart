#ifndef SCENARIO_OBS_HPP
#define SCENARIO_OBS_HPP
#include <string>
#include <map>
#include <iostream>
#include "Observer.hpp"
#include "GameEngine.hpp"
#include "GraphicEngine.hpp"


enum states { graphicEngineReady,
                       countdown,
                           sleep};

class Scenario_obs  : public Observer{

  public:
    Scenario_obs();
    ~Scenario_obs();
    virtual void update(std::string notification);
    std::string getState()
    {return state;}

    GraphicEngine* graphicE;
    GameEngine* gameE;

  private:
    states enumStates;
    std::string state;
    std::map<std::string, states> mapStates;
    bool isGraphicReady;
    int loadIterations;
};
#endif // SCENARIO_OBS_HPP
