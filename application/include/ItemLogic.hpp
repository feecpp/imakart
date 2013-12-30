#ifndef ITEMLOGIC_HPP
#define ITEMLOGIC_HPP

#include <string>

class ItemLogic{
public:
	ItemLogic(const int effect);
	~ItemLogic();

	const int getEffect();

private:
	int numEffect;
	bool used;
};

#endif