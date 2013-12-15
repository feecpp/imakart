#ifndef KARTFILE_HPP
#define KARTFILE_HPP

#include "TextFile.hpp"

class KartFile : public glimac::TextFile
{
  public:
    KartFile(const std::string& filePath);
};

#endif // KARTFILE_HPP
