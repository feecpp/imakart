#include "Map.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include <dirent.h>
#ifndef WIN32
  #include <sys/types.h>
#endif

Map::Map() :
  completed(false), position(0.f), orientation(glm::quat())
{
}

void Map::loadFromFile(const std::string& filePath)
{
  std::ifstream mapStream(filePath);
  if (!mapStream.good())
  {
    throw std::runtime_error("Impossible de charger le fichier de description de circuit " + filePath);
  }

  //Jouons avec string
  name = filePath.substr(filePath.find_last_of('/') + 1, filePath.find_last_of('.') - filePath.find_last_of('/') - 1);

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
    else if (currentWord == "FrictionArea")
    {
      loadFrictionArea(mapStream);
    }
  }

  mapStream.close();
}

std::vector<std::string> Map::findMapFiles()
{
    std::vector<std::string> fileNames;

    //Ouverture du répertoire des maps
    DIR* mapsDir = NULL;
    mapsDir = opendir("maps");
    if (mapsDir == NULL){
        std::cout << "Erreur - impossible d'accéder au répertoire des Karts" << std::endl;
    }

    //tous les fichiers du répertoire sont parcourus
    struct dirent* file = NULL;
    std::cout << "" << std::endl;
    while ((file = readdir(mapsDir)) != NULL){

        std::string tmp = std::string(file->d_name); //nom + extension
        std::size_t found = tmp.find(".");
        std::string extension = tmp.substr (found+1);
        std::string name = tmp.substr (0,found);

        if(extension == "txt"){//L'extension va ptete changer
            fileNames.push_back(name);
        }
    }

    closedir(mapsDir);
    return fileNames;
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
  assert(mapStream);

  BoundingBox bb;
  std::string attribute;

  //Pour l'instant on zappe le name;
  mapStream >> attribute;
  attribute.clear();

  //Pour l'instant a la bourrin, je sais que j'ai 2 attributs par boundingbox...
  for (int i = 0; i < 2; ++i)
  {
    mapStream >> attribute;
    if (attribute == "location")
    {
      mapStream >> bb.position.x;
      mapStream >> bb.position.y;
      mapStream >> bb.position.z;
    }
    else if (attribute == "size")
    {
      mapStream >> bb.size.x;
      mapStream >> bb.size.y;
      mapStream >> bb.size.z;
    }
  }

  boundingBoxes.push_back(bb);
}

void Map::loadItem(std::ifstream& mapStream)
{
  assert(mapStream);

  glm::vec3 itemPosition;

  std::string attribute;
  //Pour l'instant on zappe le name;
  mapStream >> attribute;
  attribute.clear();
  mapStream >> attribute; //je sais que c'est forcement "location"

  mapStream >> itemPosition.x;
  mapStream >> itemPosition.y;
  mapStream >> itemPosition.z;

  itemsPositions.push_back(itemPosition);
}

void Map::loadFrictionArea(std::ifstream& mapStream)
{
  assert(mapStream);
  //Commente tant que FrictionArea est pas défini

  FrictionArea area;
  std::string attribute;

  //Pour l'instant on zappe le name;
  mapStream >> attribute;
  attribute.clear();

  //Pour l'instant a la bourrin, je sais que j'ai 2 attributs par frictionArea...
  for (int i = 0; i < 2; ++i)
  {
    mapStream >> attribute;
    if (attribute == "location")
    {
      mapStream >> area.position.x;
      mapStream >> area.position.y;
      mapStream >> area.position.z;
    }
    else if (attribute == "size")
    {
      mapStream >> area.size.x;
      mapStream >> area.size.y;
      mapStream >> area.size.z;
    }
  }

  frictionAreas.push_back(area);
}

