#include "ItemBox.hpp"
#include "ItemLogic.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

#include <dirent.h>
#ifndef WIN32
  #include <sys/types.h>
#endif

ItemBox* ItemBox::singletonItemBox = NULL;

ItemBox* ItemBox::getSingletonItemBox(){
  if(singletonItemBox == NULL){
    singletonItemBox = new ItemBox();
  }
  return singletonItemBox;
}

void ItemBox::kill (){
  if (NULL != singletonItemBox){
    delete singletonItemBox;
    singletonItemBox = NULL;
  }
}


ItemBox::ItemBox()
{
  instancedItems.resize(0);
  itemsNames = findItemFiles();

  for(unsigned int i=0; i<itemsNames.size(); ++i){
      itemTemplates.insert(std::pair<std::string,ItemLogic*>(itemsNames[i], new ItemLogic(itemsNames[i])));
      associationIntName.insert(std::pair<int, std::string>(i+1, itemsNames[i]));
  }
}

ItemBox::~ItemBox()
{
  //Le ItemBox est responsable de la gestion memoire des items,
  //a sa mort il fait donc le menage !
  for (unsigned int i = 0; i < instancedItems.size(); ++i)
  {
    delete instancedItems[i];
  }
  auto it = itemTemplates.begin();
  for(; it != itemTemplates.end(); ++it)
  {
    delete it->second;
  }
  instancedItems.erase(instancedItems.begin(), instancedItems.end());
  itemTemplates.erase(itemTemplates.begin(), itemTemplates.end());
}

ItemLogic* ItemBox::createItemInstanceRandom()
{
  //Cette nouvelle instance est stockee dans
  //instancedItems pour pouvoir etre liberee a la destruction du ItemBox
  srand(time(NULL));
  int randomItem = rand() % itemsNames.size() + 1;
  ItemLogic* newInstance = new ItemLogic(*itemTemplates[associationIntName[randomItem]]);

  instancedItems.push_back(newInstance);
  return newInstance;
}

ItemLogic& ItemBox::getItemByName(const std::string& itemName){
  return *(itemTemplates[itemName]);
}

std::vector<std::string> ItemBox::findItemFiles(){
    std::vector<std::string> fileNames;

    //Ouverture du répertoire items
    DIR* ItemLogicsDir = NULL;
    ItemLogicsDir = opendir("items");
    if (ItemLogicsDir == NULL){
        std::cout << "Error -  Cannot read ItemLogics directory" << std::endl;
    }

    //tous les fichiers du répertoire sont parcourus
    struct dirent* file = NULL;
    std::cout << "" << std::endl;
    while ((file = readdir(ItemLogicsDir)) != NULL){

        std::string tmp = std::string(file->d_name); //nom + extension
        std::size_t found = tmp.find(".");
        std::string extension = tmp.substr (found+1);
        std::string name = tmp.substr (0,found);

        if(extension == "item"){
            fileNames.push_back(name);
        }
    }

    closedir(ItemLogicsDir);

    return fileNames;
}
