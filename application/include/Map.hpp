#pragma once

#include "Checkpoint.hpp"
#include <vector>
#include <string>

#include "Positionable.hpp"

class Map : public Positionable
{
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
        virtual const glm::vec3& getPosition() const;
        virtual const glm::quat& getOrientation() const;
    private :
        int width, height, altitude;
        std::string name;
        std::vector<Checkpoint> checkpoints;
        Checkpoint start;
        Checkpoint end;
        bool completed;
        glm::vec3 position;
        glm::quat orientation;
};

