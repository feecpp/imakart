#version 330
layout(location = 0) in vec3 iVertexPosition;

uniform mat4 model = mat4(1);
uniform mat4 viewProjection = mat4(1);
out vec3 FragColor;

void main() {
  gl_Position = viewProjection * model * vec4(iVertexPosition, 1.f);
  FragColor = vec3(1.f);
}
