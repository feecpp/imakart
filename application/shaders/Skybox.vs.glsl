#version 330
layout(location = 0) in vec3 iVertexPosition;

struct Material
{
  vec4 diffuse;
};

uniform mat4 model = mat4(1);
uniform mat4 viewProjection = mat4(1);
uniform Material material;

out vec4 FragColor;
out vec3 vPosition;

void main() {
  vec4 WVP_Pos = viewProjection * model * vec4(iVertexPosition, 1.0f);
  gl_Position = WVP_Pos.xyww;
  FragColor = material.diffuse;
  vPosition = iVertexPosition;
}
