#ifndef ITEMBOX_HPP
#define ITEMBOX_HPP

#include <string>
#include <vector>
#include <map>

class ItemLogic;

class ItemBox { 
public:

  static ItemBox* getSingletonItemBox();
  static void kill ();

  ItemLogic* createItemInstanceRandom();

  ItemLogic& getItemByName(const std::string& itemName);

  std::vector<std::string> getItemsName() const
  {
  	return itemsNames;
  }

private:
  /* Pour le singleton */
  ItemBox();
  ~ItemBox();

  static ItemBox* singletonItemBox;

  std::vector<std::string> findItemFiles();
  std::vector<std::string> itemsNames;
  std::map<int, std::string> associationIntName;

  std::map<std::string, ItemLogic*> itemTemplates;
  //Les item qui vont conretements être dans la course
  std::vector<ItemLogic* > instancedItems;

};

#endif