#version 330
layout(location = 0) in vec3 iVertexPosition;

uniform mat4 viewProjection = mat4(1);

out vec4 FragColor;
out vec3 texcoords;

void main() {
  vec4 WVP_Pos = viewProjection * vec4(iVertexPosition, 1.f);
  texcoords = iVertexPosition;
}