#ifndef ITEMINTERFACE_HPP
#define ITEMINTERFACE_HPP

#include "InterfaceElement.hpp"

class ItemInterface: public InterfaceElement{
public:
	static ItemInterface* getSingletonItemInterface();
  	static void kill ();

	const bool isSelected() const;

	void noSelected();

private:
	ItemInterface();
	~ItemInterface();

	static ItemInterface* singletonItemInterface;

	bool used;
};

#endif
