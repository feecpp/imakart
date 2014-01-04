#ifndef ITEMINTERFACE_HPP
#define ITEMINTERFACE_HPP

#include "InterfaceElement.hpp"
#include <string>

class ItemInterface: public InterfaceElement{
public:
	static ItemInterface* getSingletonItemInterface();
  	static void kill ();

	const bool isSelected() const;

	void noSelected();

	void setName(const std::string iName);

private:
	ItemInterface();
	~ItemInterface();

	static ItemInterface* singletonItemInterface;

	bool used;
};

#endif
