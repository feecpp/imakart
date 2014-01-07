#ifndef MOTIONBLUR_HPP
#define MOTIONBLUR_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "VAO.hpp"
#include "VBO.hpp"
#include "ShaderProgram.hpp"
#include <cassert>

class MotionBlur
{
public:
  MotionBlur(unsigned int windowWidth, unsigned int windowHeight);

  ~MotionBlur()
  {
    /*
    glDeleteTextures(6, blurTextures);
    glDeleteBuffers(1, &pbo);
    */
  }

  void renderFrame();

protected:
  void fillPBO();

private:
  unsigned int windowWidth;
  unsigned int windowHeight;

  unsigned int blurTarget;

  glimac::LowLevelVBO screenquadData;
  glimac::VAO screenquad;

  glimac::ShaderProgram test;

  glm::vec2 quad;
  GLuint pbo;
  GLuint blurTextures;
};

#endif // MOTIONBLUR_HPP
