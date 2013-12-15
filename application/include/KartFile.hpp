#ifndef KARTFILE_HPP
#define KARTFILE_HPP

#include "TextFile.hpp"
#include <string>
#include <map>

class KartFile
{
  public:
    KartFile(const std::string& filePath);
    std::map<std::string, std::string> getData() const
      {return Map;}
  private:
    std::map<std::string, std::string> Map;
};

#endif // KARTFILE_HPP
