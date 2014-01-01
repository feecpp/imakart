#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include "Application.hpp"

int main() {

  // Pour le "vrai jeu"
  Application app;
  sf::RenderWindow& window = app.setupEverything();
  app.startGame(window);
  return EXIT_SUCCESS;
}
