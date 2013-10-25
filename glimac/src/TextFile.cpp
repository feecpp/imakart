#include <TextFile.hpp>

using namespace glimac;

TextFile::TextFile(const std::string &fileName)
{
  fileStream.open(fileName.c_str(), std::ifstream::in);
  if (!fileStream)
  {
    isFileValid = false;
    return;
  }
  isFileValid = true;
  buffer << fileStream.rdbuf();
}

TextFile::~TextFile()
{
  fileStream.close();
}
