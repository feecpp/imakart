#pragma once

#include "VBO.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"

class MotionBlur
{
public:
  MotionBlur(unsigned int windowWidth, unsigned int windowHeight);

  ~MotionBlur()
  {

    glDeleteTextures(6, blurTextures);
    glDeleteBuffers(1, &pbo);
  }

  void renderFrame();
  void reinit();

protected:
  void fillPBO();

private:

  unsigned int windowWidth;
  unsigned int windowHeight;

  unsigned int blurTarget;
  bool motionBlurReady;

  glimac::LowLevelVBO screenquadData;
  glimac::VAO screenquad;

  glimac::ShaderProgram motionBlur;

  glm::vec2 quad[4];
  GLuint pbo;
  GLuint blurTextures[6];
};

