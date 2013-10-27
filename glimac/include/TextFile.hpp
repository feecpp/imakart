#ifndef TEXTFILE_HPP
#define TEXTFILE_HPP

#include <fstream>
#include <sstream>
#include <string>

namespace glimac
{

class TextFile
{
public:
  explicit TextFile(const std::string& fileName);
  ~TextFile();

  bool isValid() const
    {return isFileValid;}

  std::string getString() const
    {return buffer.str();}

private:
  std::ifstream fileStream;
  std::stringstream buffer;
  bool isFileValid;

};

}// namespace glimac

#endif // TEXTFILE_HPP
