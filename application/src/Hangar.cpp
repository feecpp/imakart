#include "Hangar.hpp"
#include "Kart.hpp"
#include <iostream>
#include <string>

#include <dirent.h>
#ifndef WIN32
  #include <sys/types.h>
#endif

Hangar::Hangar()
{
  playerKart = new Kart();

  findKartFiles();
}

Hangar::~Hangar()
{
  delete playerKart;
}

Kart& Hangar::getPlayerKart() const
{
  return *playerKart;
}

void Hangar::findKartFiles(){

    //Ouverture du répertoire karts
    DIR* kartsDir = NULL;
    kartsDir = opendir("karts");
    if (kartsDir == NULL){
        std::cout << "Error -  Cannot read karts directory" << std::endl;
    }

    //tous les fichiers du répertoire sont parcourus
    struct dirent* file = NULL;
    int k=0;
    while ((file = readdir(kartsDir)) != NULL){
      if(k >=2){ //Pour ne pas prendre en compte "." et ".."

        char* name = file->d_name; //nom + extension
        char* extension = strtok(name, "."); //nom
        extension = strtok(NULL, "."); //extension

        if(strcmp(extension,"kart") == 0){
            std::cout << " file with '.kart' extension found : " << name << "." << extension << std::endl;
        }
      }
      k++;
    }

    closedir(kartsDir);
}
