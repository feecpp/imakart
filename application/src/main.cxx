#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstdlib>
#include "VBO.hpp"
#include "VAO.hpp"
#include "Button2D.hpp"
#include "ButtonLogic.hpp"
#include "ShaderProgram.hpp"
#include "Checkpoint.hpp"
#include "Map.hpp"
//#include "ShaderProgram.hpp"
#include "Application.hpp"



int main() {

  // Pour le "vrai jeu"
  Application app;
  sf::RenderWindow& window = app.setupEverything();
  app.startGame(window);
  return EXIT_SUCCESS;
}
