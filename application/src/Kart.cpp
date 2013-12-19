#include "Kart.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <SFML/System.hpp>
#include <KartFile.hpp>
#include <iostream>

/////// Site qui a l'air pratique pour la physique : http://www.formules-physique.com/categorie/687 //////////////

Kart::Kart()
    : position(0.f, 0.1f, 0.f), orientation(glm::angleAxis(0.f, glm::vec3(0.f, 1.f, 0.f))),
      directionAngle(0.f), speed(0.f), currentAngularSpeed(0.f), currentAcceleration(0.f), accelerationState(DO_NOT_MOVE), moveState(NONE), turnState(NOTURN), name("standard")
{
}

Kart::Kart(std::string kartName)
    : position(0.f, 0.1f, 0.f), orientation(glm::angleAxis(0.f, glm::vec3(0.f, 1.f, 0.f))),
      directionAngle(0.f), speed(0.f), currentAngularSpeed(0.f), currentAcceleration(0.f), accelerationState(DO_NOT_MOVE), moveState(NONE), turnState(NOTURN)
{
  const std::string path = "karts/"+kartName+".kart";

  //Je crée un KartFile à partir du fichier.kart et récupère un std::map
  KartFile kartFile(path);
  std::map<std::string, std::string> map = kartFile.getData();

  //Mise a jour des specs à partir de la std::map
  name = map["Name"];
  specifications.acceleration = (float)(atoi(map["Acceleration"].c_str()));
  specifications.maxSpeed = (float)(atoi(map["MaxSpeed"].c_str()));
  specifications.weight = atoi(map["Weight"].c_str());
 }

Kart::Kart(glm::vec3 position, glm::quat orientation, float speed)
  : position(position), orientation(orientation), speed(speed)
{
}

Kart::Kart(const Kart& kartToCopy)
  : position(kartToCopy.position), orientation(kartToCopy.orientation), directionAngle(0.f), speed(kartToCopy.speed),
    currentAngularSpeed(0.f), currentAcceleration(0.f), accelerationState(DO_NOT_MOVE), moveState(NONE), turnState(NOTURN), name(kartToCopy.name)
{
  specifications = kartToCopy.specifications;
}

Kart::~Kart()
{
}

void Kart::update(float elapsedTimeInSecond)
{
  //Calcul de la nouvelle direction en fonction de l'angularSpeed
  if (speed != 0.f)
  {
    directionAngle += currentAngularSpeed * (elapsedTimeInSecond); //en degres/secondes
  }
  orientation = glm::angleAxis(directionAngle, glm::vec3(0.f, 1.f, 0.f));

  const glm::vec3 initialDirection = glm::vec3(0.f, 0.f, -1.f);
  glm::vec3 direction = glm::normalize(glm::toMat3(orientation) * initialDirection);

  //Tentative d'implémentation d'une base de physique : http://www.onversity.net/cgi-bin/progactu/actu_aff.cgi?Eudo=bgteob&P=00000551
  float travelledDistance = 0.f;

  if (accelerationState == MAX_SPEED_REACHED)
  {
    travelledDistance = speed * elapsedTimeInSecond;
  }
  else
  {
    travelledDistance = speed * elapsedTimeInSecond + currentAcceleration * (elapsedTimeInSecond * elapsedTimeInSecond) / 2.f;
  }

  /* Si on est en phase de deceleration et qu'on bouge pas c'est qu'on
   * a fini la phase de deceleration et qu'on est a l'arret, il faut donc
   * empecher le kart de repartir dans l'autre sens ! Si la vitesse passe d'un coup d'un signe a l'autre
   * (positif / negatif et vice versa) en phase de deceleration c'est aussi qu'on doit s'arreter c'est juste qu'on a decelere
   * trop vite et qu'on a passe le zero...
   */
  float supposedNewSpeed = travelledDistance / elapsedTimeInSecond;
  if ( (abs(speed - 0.f) <= 0.000001f || supposedNewSpeed / speed < 0.f) && accelerationState == DECELERATE)
  {
    currentAcceleration = 0.f;
    travelledDistance = 0.f;
    speed = 0.f;
    accelerationState = DO_NOT_MOVE;
    moveState = NONE;
    turnState = NOTURN;
  }
  else
  {
    //Update speed for next calculation ! (speed = initialSpeed)
    speed = supposedNewSpeed;
    if (abs(speed) >= specifications.maxSpeed && accelerationState != MAX_SPEED_REACHED)
    {
      accelerationState = MAX_SPEED_REACHED;
      if (speed > 0.f)
        speed = specifications.maxSpeed;
      else speed = - specifications.maxSpeed;
    }
  }
  position += direction * travelledDistance;//en uniteOGL/seconde
}

void Kart::moveForward() //enclenche la marche avant
{
  //uniteOpenGL / seconde
  if(moveState == BACKWARD){ //Si on est en marche arriere et qu'on accelerait alors il faut faire un arret brutale et accelerer
    brake();
  }else{
    currentAcceleration = specifications.acceleration;
    accelerationState = ACCELERATE;
    moveState = FORWARD;
  }
}

void Kart::moveBackward() //enclenche la marche arriere
{
  //uniteOpenGL / seconde
  if(moveState == FORWARD){ //Si on est en marche avant et qu'on accelerait alors il faut freiner
    brake();
  }else{
    currentAcceleration = - specifications.acceleration;
    accelerationState = ACCELERATE;
    moveState = BACKWARD;
  }
}

void Kart::turnLeft()
{
  turnState = LEFT;
  if(moveState == BACKWARD){
    currentAngularSpeed = -specifications.angularSpeed;
  }else if(moveState == FORWARD){
    currentAngularSpeed = specifications.angularSpeed;
  }
}

void Kart::turnRight()
{
  turnState = RIGHT;
  if(moveState == BACKWARD){
    currentAngularSpeed = specifications.angularSpeed;
  }else if(moveState == FORWARD){
    currentAngularSpeed = -specifications.angularSpeed;
  }
}

void Kart::stopMoveForward()
{
  if (accelerationState == DECELERATE)
    return;
  currentAcceleration = -currentAcceleration;
  accelerationState = DECELERATE;
}

void Kart::stopMoveBackward()
{
  if (accelerationState == DECELERATE)
    return;
  currentAcceleration = -currentAcceleration;
  accelerationState = DECELERATE;
}

void Kart::stopTurning()
{
  currentAngularSpeed = 0.f;
}

//Le freinage est juste une deceleration plus puissante pour l'instant
void Kart::brake()
{
  //Si on est deja en train de decelerer il faut juste augmenter l'acceleration courante
  if (accelerationState == DECELERATE)
  {
    currentAcceleration = specifications.breakingCoefficient * currentAcceleration;
  }
  //Sinon il faut carrement prendre son oppose
  else
  {
    accelerationState = DECELERATE;
    currentAcceleration = - specifications.breakingCoefficient * currentAcceleration;
  }
}

void Kart::drift() //Pas encore géré
{
  brake();
}

const glm::vec3& Kart::getPosition() const
  {return position;}

const glm::quat& Kart::getOrientation() const
  {return orientation;}
