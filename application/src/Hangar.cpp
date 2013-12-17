#include "Hangar.hpp"
#include <iostream>

#include <dirent.h>
#ifndef WIN32
  #include <sys/types.h>
#endif

Hangar::Hangar()
{
  instancedKarts.resize(0);
  kartNames = findKartFiles();
  for(unsigned int i=0; i<kartNames.size(); ++i){
      kartTemplates.insert(std::pair<std::string,Kart*>(kartNames[i], new Kart(kartNames[i])));
  }
}

Hangar::~Hangar()
{
  //Le hangar est responsable de la gestion memoire des Karts,
  //a sa mort il fait donc le menage !
  for (unsigned int i = 0; i < instancedKarts.size(); ++i)
  {
    delete instancedKarts[i];
  }
  auto it = kartTemplates.begin();
  for(; it != kartTemplates.end(); ++it)
  {
    delete it->second;
  }
  instancedKarts.erase(instancedKarts.begin(), instancedKarts.end());
  kartTemplates.erase(kartTemplates.begin(), kartTemplates.end());
}

Kart& Hangar::createKartInstanceByName(const std::string& kartName)
{
  //Cette nouvelle instance est stockee dans
  //instancedKarts pour pouvoir etre liberee a la destruction du Hangar
  Kart* newInstance = nullptr;
  if(kartTemplates[kartName] != nullptr)
  {
    //Creation du nouveau Kart par copie du modele charge depuis le fichier kart
    newInstance = new Kart(*kartTemplates[kartName]);
  }else
  {
    newInstance = kartTemplates["unicorn"]; //par défaut
  }
  instancedKarts.push_back(newInstance);
  return *newInstance;
}

std::vector<std::string> Hangar::findKartFiles(){
    std::vector<std::string> fileNames;

    //Ouverture du répertoire karts
    DIR* kartsDir = NULL;
    kartsDir = opendir("karts");
    if (kartsDir == NULL){
        std::cout << "Error -  Cannot read karts directory" << std::endl;
    }

    //tous les fichiers du répertoire sont parcourus
    struct dirent* file = NULL;
    std::cout << "" << std::endl;
    while ((file = readdir(kartsDir)) != NULL){

        std::string tmp = std::string(file->d_name); //nom + extension
        std::size_t found = tmp.find(".");
        std::string extension = tmp.substr (found+1,found+1);
        std::string name = tmp.substr (0,found);

        if(extension == "kart"){
            fileNames.push_back(name);
        }
    }

    closedir(kartsDir);
    return fileNames;
}
