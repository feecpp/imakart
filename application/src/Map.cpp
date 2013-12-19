#include "Map.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>

Map::Map() :
  completed(false) {
}

void Map::loadFromFile(const std::string& filePath)
{
  std::ifstream mapStream(filePath);
  if (!mapStream.good())
  {
    throw std::runtime_error("Impossible de charger le fichier de description de circuit " + filePath);
  }

  std::string currentWord;
  while (mapStream >> currentWord)
  {
    if (currentWord == "Checkpoint")
    {
      loadCheckpoint(mapStream);
    }
    else if (currentWord == "Item")
    {
      loadItem(mapStream);
    }
    else if (currentWord == "BoundingBox")
    {
      loadBoundingBox(mapStream);
    }
  }

  mapStream.close();
  //DEBUG
  for (auto it = checkpoints.begin(); it != checkpoints.end(); ++it)
    std::cout << "Pos : " << it->position.x << "; " << it->position.y << "; " << it->position.z << ". radius : " << it->radius << std::endl;
 }

const std::string& Map::getName() const{
    return this->name;
}

const std::vector<Checkpoint>& Map::getCheckpoints() const{
    return this->checkpoints;
}

Checkpoint Map::getStart() const{
    return this->start;
}

Checkpoint Map::getEnd() const{
    return this->end;
}

const glm::vec3& Map::getPosition() const
  {return position;}

const glm::quat& Map::getOrientation() const
{return orientation;}

void Map::loadCheckpoint(std::ifstream& mapStream)
{
  assert(mapStream);

  Checkpoint checkpoint;

  std::string attribute;
  //Pour l'instant on zappe le name;
  mapStream >> attribute;
  attribute.clear();

  //Pour l'instant a la bourrin, je sais que j'ai 2 attributs par checkpoint...
  for (int i = 0; i < 2; ++i)
  {
    mapStream >> attribute;
    if (attribute == "location")
    {
      mapStream >> checkpoint.position.x;
      mapStream >> checkpoint.position.y;
      mapStream >> checkpoint.position.z;
    }
    else if (attribute == "radius")
    {
      mapStream >> checkpoint.radius;
    }
  }
  checkpoints.push_back(checkpoint);
}

void Map::loadBoundingBox(std::ifstream& mapStream)
{
}

void Map::loadItem(std::ifstream& mapStream)
{
}

