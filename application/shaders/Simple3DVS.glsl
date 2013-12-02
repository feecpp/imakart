#version 330
layout(location = 0) in vec3 iVertexPosition;
layout(location = 1) in vec2 iTexCoord;
layout(location = 2) in vec3 iNormals;

struct Material
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
};

uniform mat4 model = mat4(1);
uniform mat4 viewProjection = mat4(1);
uniform Material material;

out vec4 FragColor;

void main() {
  gl_Position = viewProjection * model * vec4(iVertexPosition, 1.f);
  FragColor = material.ambient + material.diffuse + material.specular;
}
