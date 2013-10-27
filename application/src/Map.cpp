#include "Map.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>

Map::Map() :
    width(0), height(0), altitude(0), completed(false) {
}

void Map::loadData(const char* path){

    std::ifstream fichier(path);  // File opened
    if(fichier)
    {
        //Read the first line : name of the map
        getline(fichier, this->name);

        //Get the width
        std::string keyword;
        fichier >> keyword;
        if(keyword=="width"){
            fichier >> this->width;
        }

        //Get the height
        fichier >> keyword;
        if(keyword=="height"){
            fichier >> this->height;
        }

        //Get the altitude
        fichier >> keyword;
        if(keyword=="altitude"){
            fichier >> this->altitude;
        }

        //Set the checkpoints in the map
        fichier >> keyword;
        glm::vec3 point;
        int i=0;
        while(keyword=="Checkpoint"){
            fichier >> point.x;
            fichier >> point.y;
            fichier >> point.z;
            Checkpoint checkpoint(point, 4, 2, 1);
            this->checkpoints.push_back(checkpoint);
            fichier >> keyword;
            i++;
        }
        this->start = this->checkpoints[0];
        this->end = this->checkpoints[this->checkpoints.size()-1];

        fichier.close();
    }
    else{
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
    }

}

int Map::getWidth(){
    return this->width;
}

int Map::getHeight(){
    return this->height;
}

int Map::getAltitude(){
    return this->altitude;
}

std::string Map::getName(){
    return this->name;
}

std::vector<Checkpoint> Map::getCheckpoints(){
    return this->checkpoints;
}

Checkpoint Map::getStart(){
    return this->start;
}

Checkpoint Map::getEnd(){
    return this->end;
}

bool Map::isCompleted(){
   return this->completed;
}

