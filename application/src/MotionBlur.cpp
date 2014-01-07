#include "MotionBlur.hpp"
#include <stdlib.h>
#include <cstring>
#include <iostream>

MotionBlur::MotionBlur(unsigned int windowWidth, unsigned int windowHeight)
  /*: windowWidth(windowWidth), windowHeight(windowHeight), blurTarget(0)*/
{
  /*
  // Create blur textures
  glGenTextures(6, blurTextures);
  // Allocate a pixel buffer to initialize textures and PBOs
  unsigned int pixelDataSize = windowWidth * windowHeight * 3 * sizeof(unsigned char);
  void* data = (void*)malloc(pixelDataSize);
  memset(data, 0x00, pixelDataSize);
  // Setup 6 texture units for blur effect
  // Initialize texture data
  for (int i=0; i<6;i++)
  {
    glActiveTexture(GL_TEXTURE1+i);
    glBindTexture(GL_TEXTURE_2D, blurTextures[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowWidth, windowHeight, 0, GL_RGB,
    GL_UNSIGNED_BYTE, data);
  }
  // Allocate space for copying pixels so we don’t call malloc on every draw
  glGenBuffers(1, &pbo);
  glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo);
  glBufferData(GL_PIXEL_PACK_BUFFER, pixelDataSize, data, GL_DYNAMIC_COPY);
  glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

  free(data);

  quad[0] = glm::vec2(-1.f, -1.f);
  quad[1] = glm::vec2(-1.f, 1.f);
  quad[2] = glm::vec2(1.f, 1.f);
  quad[3] = glm::vec2(1.f, -1.f);
 // screenquadData.setBufferData(quad, 4 * sizeof(glm::vec2), GL_STATIC_DRAW);
 // screenquad.enableVertexAttribArray(0);
//  screenquad.vertexAttribPointer(screenquadData, 0, 1, GL_FLOAT, GL_TRUE, 0, (const GLvoid* ) NULL);

  motionBlur.loadProgram("shaders/motionBlurVS.glsl", "shaders/motionBlurFS.glsl");
  std::string logInfo;
  if (!motionBlur.compileAndLinkShaders(logInfo))
  {
    std::cerr << logInfo << std::endl;
    assert(false);
  }
  */
}

void MotionBlur::renderFrame()
{
  /*
  fillPBO();
  //draw
  glDisable(GL_DEPTH_TEST);
  motionBlur.use();
 // screenquad.bind();
  //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  //screenquad.unbind();
  glEnable(GL_DEPTH_TEST);

  blurTarget++;
  if (blurTarget >= 6)
    blurTarget = 0;
    */
}

void MotionBlur::fillPBO()
{
  /*
  glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo);
  glReadPixels(0, 0, windowWidth, windowHeight, GL_RGB,
  GL_UNSIGNED_BYTE, NULL);
  glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
  // Next bind the PBO as the unpack buffer,
  // then push the pixels straight into the texture
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
  // Setup texture unit for new blur, this gets imcremented every frame
  glActiveTexture(GL_TEXTURE0+blurTarget );
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, windowWidth, windowHeight,
  0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
  */
}
