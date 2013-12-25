#ifndef HANGAR_HPP
#define HANGAR_HPP

#include <vector>
#include <string>
#include <map>

#include "Kart.hpp"
/**
 * @brief The Hangar class représente un hangar qui gère les Kart.
 * Concrètement c'est lui qui va créer des Karts et gérer leur allocation mémoire.
 * Ca peut etre là aussi qu'on gère le chargement des types de Kart etc...
 */
// Cette classe est à modifier pour l'instant c'est juste un embryon qui offre une méthode utilitaire :
// => getPlayerKart() et gère ce Kart. Il faudra qu'elle soit capable de gérer un nombre indéfini de Kart
// par la suite.
class Hangar
{
public:
  static Hangar* getSingletonHangar();
  static void kill ();
  Kart& createKartInstanceByName(const std::string& kartName);

  std::vector<std::string> getKartsName() const
  {
  	return kartNames;
  }

private:
  /* Pour le singleton */
  Hangar();
  ~Hangar();

  static Hangar* singletonHangar;
  std::vector<std::string> findKartFiles();
  std::vector<std::string> kartNames;
  //En fait on pourrait juste stocker des Kart::Specifications
  std::map<std::string, Kart*> kartTemplates;
  //Les karts qui vont conretements rouler dans une course
  std::vector<Kart* > instancedKarts;
};

#endif // HANGAR_HPP
