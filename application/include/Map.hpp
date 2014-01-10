#pragma once

#include "Checkpoint.hpp"
#include <vector>
#include <string>
#include <BoundingBox.hpp>
#include <glm/glm.hpp>
#include "ItemGenerator.hpp"

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

  const std::vector<Checkpoint>& getPlayerCheckpoints() const
    {return playerCheckpoints;}

  const std::vector<Checkpoint>& getOpponentCheckpoints() const
    {return opponentCheckpoints;}

  const std::vector<ItemGenerator*>& getItemsGenerators() const
    {return itemsGenerator;}

  const std::vector<BoundingBox* >& getBoudingBoxes() const
    {return boundingBoxes;}

  const std::vector<FrictionArea>& getFrictionAreas() const
    {return frictionAreas;}

  const std::vector<glm::vec3>& getKartStartingPoints() const
    {return kartStartingPoints;}

  /* TODO
  Checkpoint getStart() const;
  Checkpoint getEnd() const;
  */

  virtual const glm::vec3& getPosition() const;
  virtual const glm::quat& getOrientation() const;
  virtual const bool isVisible() const
    {return visible;}

private :
  void loadCheckpoint(std::ifstream& mapStream, bool playerCheckpoint);
  void loadBoundingBox(std::ifstream& mapStream);
  void loadItem(std::ifstream& mapStream);
  void loadFrictionArea(std::ifstream& mapStream);
  void loadStartingPoint(std::ifstream& mapStream);

  ///Le nom de la map est pour l'instant le nom du fichier
  ///qui contenait sa description, sans l'extension
  std::string name;

  std::vector<Checkpoint> playerCheckpoints;
  std::vector<Checkpoint> opponentCheckpoints;
  std::vector<BoundingBox* > boundingBoxes;
  std::vector<ItemGenerator*> itemsGenerator;
  std::vector<FrictionArea> frictionAreas;
  std::vector<glm::vec3> kartStartingPoints;
  bool completed;

  glm::vec3 position;
  glm::quat orientation;
  bool visible;
};

