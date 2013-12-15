#include "KartFile.hpp"
#include <iostream>
#include <vector>

KartFile::KartFile(const std::string& filePath){

  std::ifstream fileStream;
  fileStream.open(filePath);

  std::string tmp;
  while (fileStream >> tmp)
  {
    std::string key = tmp;
    fileStream >> tmp;
    std::string value = tmp;
    Map.insert(std::pair<std::string,std::string>(key, value));
  }

  fileStream.close();
}
