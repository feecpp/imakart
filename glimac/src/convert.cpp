#include "convert.hpp"

std::string glimac::convert (float number){
  std::ostringstream buff;
  buff<<number;
  return buff.str();   
}