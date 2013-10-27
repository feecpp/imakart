#version 330
layout(location = 0) in vec3 iVertexPosition;

uniform mat4 MVP = mat4(1);

void main() {
  gl_Position = MVP * vec4(iVertexPosition, 1.f);
}
