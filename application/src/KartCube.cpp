#include "KartCube.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Positionable.hpp"
#include <cstddef>
#include <ShaderProgram.hpp>

KartCube::KartCube()
{
  vertices[0].position = glm::vec3(-0.5f, -0.5f, 0.5f);
  vertices[1].position = glm::vec3(0.5f, -0.5f, 0.5f);
  vertices[2].position = glm::vec3(-0.5f, 0.5f, 0.5f);
  vertices[3].position = glm::vec3(0.5f, 0.5f, 0.5f);
  vertices[4].position = glm::vec3(-0.5f, -0.5f, -0.5f);
  vertices[5].position = glm::vec3(0.5f, -0.5f, -0.5f);
  vertices[6].position = glm::vec3(-0.5f, 0.5f, -0.5f);
  vertices[7].position = glm::vec3(0.5f, 0.5f, -0.5f);

  indices[0] = 0; indices[1] = 1;
  indices[2] = 2; indices[3] = 3;
  indices[4] = 7; indices[5] = 1;
  indices[6] = 5; indices[7] = 4;
  indices[8] = 7; indices[9] = 6;
  indices[10] = 2; indices[11] = 4;
  indices[12] = 0; indices[13] = 1;

  modelMatrix = glm::mat4(1.);
  vbo.setBufferData((const GLvoid* ) glm::value_ptr(vertices[0].position), verticesSize(), GL_STATIC_DRAW);

  vao.enableVertexAttribArray(0);
  vao.vertexAttribPointer(vbo, 0, 3, GL_FLOAT, GL_TRUE, sizeof(glimac::Vertex3D), (const GLvoid* ) offsetof(glimac::Vertex3D, position));
}

void KartCube::draw(const glimac::ShaderProgram& shaderProgram) const
{
  GLint modelMatrixIndex = shaderProgram.getUniformIndex("MVP");
  shaderProgram.setUniform(modelMatrixIndex, modelMatrix);
  vao.bind();
  glDrawElements(GL_TRIANGLE_STRIP, indicesSize(), GL_UNSIGNED_SHORT, (const GLvoid*) indices);
  vao.unbind();
}

#include <iostream>
void KartCube::update()
{
  modelMatrix = glm::translate(modelMatrix, model->getPosition());
}
