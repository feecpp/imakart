#version 330
layout(location = 0) in vec3 iVertexPosition;
layout(location = 1) in vec2 iTexCoord;
layout(location = 2) in vec3 iNormals;

struct Material
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};

uniform mat4 model = mat4(1);
uniform mat4 uView;
uniform mat4 uNormal;
uniform mat4 viewProjection = mat4(1);
uniform Material material;

out vec4 FragColor;
out vec4 vNormal_vs;
out vec4 vPosition_vs;
out vec2 TexCoord;


void main() {
  //Coordonnées homogènes
  vec4 vertexPosition = vec4(iVertexPosition, 1);
  vec4 vertexNormal = vec4(iNormals, 0);

  //Calcul des valeurs de sortie
  FragColor = material.ambient + material.diffuse + material.specular;
  vNormal_vs = uNormal * vertexNormal;
  vPosition_vs =  uView * model * vertexPosition;

  TexCoord = iTexCoord;
  gl_Position = viewProjection * model * vec4(iVertexPosition, 1.f);
}
