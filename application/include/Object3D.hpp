#ifndef OBJECT3D_HPP
#define OBJECT3D_HPP

class Positionable;

/**
 * @brief Classe abstraite représentant un objet 3D capable de se dessiner.
 * S'inspire du Design Pattern MVC. Ici Object3D représente la vue, et l'interface
 * Positionable le modèle que la vue affiche.
 */
class Object3D
{
public:
  virtual ~Object3D() {}
  virtual void draw() const = 0;

  /**
   * @brief update : l'objet 3D doit se mettre à jour
   * à chaque frame pour correspondre au nouvel état de son modèle.
   */
  virtual void update() = 0;

  /**
   * @brief setModelToRepresent lie l'objet 3D à une représentation logique
   * qu'il va exprimer graphiquement.
   * @param myModel l'objet du modèle (dans l'esprit MVC) que l'objet 3D
   * va représenter. Ce peut etre par exemple un Kart. Le modele doit implémenter
   * l'interface Positionable car pour etre représenté en 3D il doit avoir une position
   * ainsi qu'une orientation.
   */
  void setModelToRepresent(const Positionable& myModel)
    {model = &myModel;}

protected:
  const Positionable* model;

};

#endif // OBJECT3D_HPP
