#ifndef ITEMLOGIC_HPP
#define ITEMLOGIC_HPP

#include <string>

class ItemLogic{
public:
	ItemLogic(std::string name);
	~ItemLogic();

	const std::string getEffect();

private:
	std::string name;
	std::string effect;
	bool used;
};

#endif