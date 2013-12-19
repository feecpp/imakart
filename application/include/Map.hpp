#pragma once

#include "Checkpoint.hpp"
#include <vector>
#include <string>

#include "Positionable.hpp"

class Map : public Positionable
{
public:
  Map();
  void loadFromFile(const std::string& filePath);

  const std::vector<Checkpoint>& getCheckpoints() const;
  const std::string& getName() const;

  //TODO
  /*
  std::vector<Item>& getItems();
  std::vector<BoudingBox>& getBoudingBoxes();
  std::vector<FrictionArea>& getFrictionAreas();
  */

  Checkpoint getStart() const;
  Checkpoint getEnd() const;

  virtual const glm::vec3& getPosition() const;
  virtual const glm::quat& getOrientation() const;

private :
  void loadCheckpoint(std::ifstream& mapStream);
  void loadBoundingBox(std::ifstream& mapStream);
  void loadItem(std::ifstream& mapStream);

  ///Le nom de la map est pour l'instant le nom du fichier
  ///qui contenait sa description, sans l'extension
  std::string name;
  std::vector<Checkpoint> checkpoints;
  Checkpoint start;
  Checkpoint end;
  bool completed;
  glm::vec3 position;
  glm::quat orientation;
};

