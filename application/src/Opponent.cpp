#include "Opponent.hpp"
#include "Kart.hpp"
#include <iostream>
#include <cmath>

#ifndef M_PI
   #define M_PI 3.14159265358979323846
#endif

Opponent::Opponent(Kart& kart)
  :opponentKart(kart), angle(0.f), heading(0.f), x(0.f), z(0.f)
{
  checkpoints.resize(0);
}

const Kart& Opponent::getKart() const
{
  return opponentKart;
}

Kart& Opponent::getKart()
{
  return opponentKart;
}

void Opponent::fillCheckpoints(const std::vector<Checkpoint> checkpoints)
{
  this->checkpoints = checkpoints;
}

void Opponent::validateCheckpoints()
{
  unsigned int cpt = 0;
  for (auto it = checkpoints.begin(); it != checkpoints.end(); ++it)
  {
    if (it->contains(opponentKart.getPosition()))
    {
      //je vais chercher le checkpoint valide
      //std::cout <<"position du checkpoint valide x : "<< it->position.x << std::endl;
     // std::cout <<"position du checkpoint valide z : "<< it->position.z << std::endl;
      std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
      std::cout <<"checkpoint actuel : "<< cpt << std::endl;

      //je vais chercher le checkpoint suivant
      if(cpt == checkpoints.size()-1){
        cpt = 0;
      }else{
        cpt++;
      }

      std::cout <<"checkpoint suivant : "<< cpt<< std::endl;
      std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

      x = checkpoints[cpt].position.x - opponentKart.getPosition().x;
      z = checkpoints[cpt].position.z - opponentKart.getPosition().z;
     // std::cout <<"x : "<< x << std::endl;
    //  std::cout <<"z : "<< z << std::endl;

      //Calcul de l'angle
      //angle = 2* atan(z / (x + sqrt(x*x + z*z)));
     // std::cout <<"angle radian : "<< angle << std::endl;
      //angle = angle * 360.f / (2*M_PI);
      //std::cout <<"angle degres : "<< angle << std::endl;


      //std::cout <<"heading "<< qx << "," << qy << "," <<  qz << std::endl;
      //std::cout <<"attitude "<< attitude<< std::endl;
      //std::cout <<"bank "<< bank << std::endl;


      //std::cout <<"position du checkpoint suivant x : "<< checkpoints[cpt].position.x << std::endl;
     // std::cout <<"position du checkpoint suivant z : "<< checkpoints[cpt].position.z << std::endl;
     // std::cout <<"cpt : "<< cpt << std::endl;

      // calcul de l'angle

      //actualisation mouvement
    }
    cpt++;

  }
  cpt = 0;

  angle = 2* atan(z / (x + sqrt(x*x + z*z)));
  angle = angle * 360.f / (2*M_PI);

  std::cout << "----------------------------------------------------------" << std::endl;
  std::cout <<"x  "<< x << std::endl;
  std::cout <<"z  "<< z << std::endl;
  std::cout <<"angle  "<< angle << std::endl;

  float qx = opponentKart.getOrientation().x;
  float qy = opponentKart.getOrientation().y;
  float qz = opponentKart.getOrientation().z;
  float qw = opponentKart.getOrientation().w;


  heading = (atan2(2*qy*qw-2*qx*qz , 1 - 2*qy*qy - 2*qz*qz)) * 360.f / (2*M_PI);
  std::cout <<"heading  "<< heading << std::endl;
  if(angle != 0.f){
    if((-90.f - angle) > -180.f){
      if(heading <= (-90.f - angle -1.5f) || heading >= (-90.f - angle +1.5f)){
        std::cout <<"right " << std::endl;
        opponentKart.moveForward();
       // if(fabs(heading) - fabs(-90.f - angle) <0){
          opponentKart.turnRight();
        //}else{
         // opponentKart.turnLeft();
        //}
      }else{
        std::cout <<"dontmove " << std::endl;
        opponentKart.stopTurning();
      }
    }else{
      if(heading <= (-90.f - angle -1.5f +360.f) || heading >= (-90.f - angle +1.5f +360.f)){
       // std::cout <<"right+ " << std::endl;
        opponentKart.moveForward();
        //if(fabs(heading) - fabs(angle) <0){
          opponentKart.turnRight();
        //}else{
          //opponentKart.turnLeft();
        //}
      }else{
        //std::cout <<"dontmove+" << std::endl;
        opponentKart.stopTurning();
      }
    }
  }
  std::cout << "----------------------------------------------------------" << std::endl;
}

void Opponent::startMovement(){
   //opponentKart.moveForward();
   //opponentKart.turnLeft();
}



