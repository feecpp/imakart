#include "Hangar.hpp"
#include "Kart.hpp"
#include <iostream>

#include <dirent.h>
#ifndef WIN32
  #include <sys/types.h>
#endif

Hangar::Hangar()
{
  kartNames = findKartFiles();

  for(unsigned int i=0; i<kartNames.size(); ++i){
      kartsHangar.insert(std::pair<std::string,Kart*>(kartNames[i], new Kart(kartNames[i])));
  }

  //Par défaut, après il faudra récupérer choix du menu
  playerKart = kartsHangar["fusee"];
}

Hangar::~Hangar()
{
  delete playerKart;
}

Kart& Hangar::getPlayerKart() const
{
  return *playerKart;
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
    int k=0;
    std::cout << "" << std::endl;
    while ((file = readdir(kartsDir)) != NULL){
      if(k >=2){ //Pour ne pas prendre en compte "." et ".."

        std::string tmp = std::string(file->d_name); //nom + extension
        std::size_t found = tmp.find(".");
        std::string extension = tmp.substr (found+1,found+1);
        std::string name = tmp.substr (0,found);

        if(extension == "kart"){
            fileNames.push_back(name);
        }
      }
      k++;
    }

    closedir(kartsDir);
    return fileNames;
}
