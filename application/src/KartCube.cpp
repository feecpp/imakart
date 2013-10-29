#include "KartCube.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Positionable.hpp"

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

  modelMatrix = glm::mat4(1.);
  vbo.setBufferData((const GLvoid* ) glm::value_ptr(vertices[0].position), verticesSize(), GL_STATIC_DRAW);

  vao.enableVertexAttribArray(0);
  vao.vertexAttribPointer(vbo, 0, 3, GL_FLOAT, GL_TRUE, sizeof(glimac::Vertex3D), (const GLvoid* ) offsetof(glimac::Vertex3D, position));
}

void KartCube::draw() const{
  vao.bind();
  glDrawElements(GL_TRIANGLE_STRIP, indicesSize(), GL_UNSIGNED_SHORT, (const GLvoid*) indices);
  vao.unbind();
}

void KartCube::update()
{
  modelMatrix = glm::translate(modelMatrix, model->getPosition());
}
