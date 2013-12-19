#pragma once

#include "Checkpoint.hpp"
#include <vector>
#include <string>
#include <BoundingBox.hpp>
#include <glm/glm.hpp>

#include "Positionable.hpp"

/**
 * @brief The FrictionArea struct
 * Represente une zone de friction sur le circuit.
 * Devra contenir un coefficient de friction quand ce
 * sera gere par le blender exporter.
 */
struct FrictionArea
{
  glm::vec3 position;
  glm::vec3 size;
};

class Map : public Positionable
{
public:
  /**
   * @brief findMapFiles
   * Renvoie un vector contenant tous les noms des fichiers
   * maps presents dans le repertoire des maps
   */
  static std::vector<std::string> findMapFiles();

  Map();
  ~Map();
  void loadFromFile(const std::string& filePath);

  const std::string& getName() const
    {return name;}
  const std::vector<Checkpoint>& getCheckpoints() const
    {return checkpoints;}
  const std::vector<glm::vec3>& getItemsPositions() const
    {return itemsPositions;}
  const std::vector<BoundingBox>& getBoudingBoxes() const
    {return boundingBoxes;}
  const std::vector<FrictionArea>& getFrictionAreas() const
    {return frictionAreas;}

  /* TODO
  Checkpoint getStart() const;
  Checkpoint getEnd() const;
  */

  virtual const glm::vec3& getPosition() const;
  virtual const glm::quat& getOrientation() const;

private :
  void loadCheckpoint(std::ifstream& mapStream);
  void loadBoundingBox(std::ifstream& mapStream);
  void loadItem(std::ifstream& mapStream);
  void loadFrictionArea(std::ifstream& mapStream);

  ///Le nom de la map est pour l'instant le nom du fichier
  ///qui contenait sa description, sans l'extension
  std::string name;

  std::vector<Checkpoint> checkpoints;
  std::vector<BoundingBox> boundingBoxes;
  std::vector<glm::vec3> itemsPositions;
  std::vector<FrictionArea> frictionAreas;
  bool completed;

  glm::vec3 position;
  glm::quat orientation;
};

