#ifndef OBJECTFILE_HPP
#define OBJECTFILE_HPP

/**
  * @Brief pour rendre le kartFile plus générique au niveau du nom, car il sert aussi pour les items
  */

#include "TextFile.hpp"
#include <string>
#include <map>

class ObjectFile
{
  public:
    ObjectFile(const std::string& filePath);
    std::map<std::string, std::string> getData() const
      {return Map;}
  private:
    std::map<std::string, std::string> Map;
};

#endif // OBJECTFILE_HPP
