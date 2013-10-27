#pragma once

#include "Checkpoint.hpp"
#include <vector>
#include <string>

class Map {
    private :
        int width, height, altitude;
        std::string name;
        std::vector<Checkpoint> checkpoints;
        Checkpoint start;
        Checkpoint end;
        bool completed;


    public:
        Map();
        void loadData(const char* path);
        int getWidth();
        int getHeight();
        int getAltitude();
        std::string getName();
        std::vector<Checkpoint> getCheckpoints();
        Checkpoint getStart();
        Checkpoint getEnd();
        bool isCompleted();
};

