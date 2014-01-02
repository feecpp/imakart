#ifndef CONVERT_HPP
#define CONVERT_HPP

#include <sstream>

namespace glimac{
	template<typename T>
	std::string convertToString (const T& number){
 		std::ostringstream buff;
 		buff<<number;
 	 return buff.str();   
	}
	template<typename T>
	std::string convertToIntString (const T& number){
 		std::ostringstream buff;
 		buff<<(int)number;
 	 return buff.str();   
	}
}
#endif 