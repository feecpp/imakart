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
out vec3 vNormal_vs;
out vec3 vPosition;
//En rapport avec material
out vec3 Kd;
out vec3 Ks;
out float shine;


void main() {
  //Coordonnées homogènes
  vec4 vertexPosition = vec4(iVertexPosition, 1);
  vec4 vertexNormal = vec4(iNormals, 0);

  //Calcul des valeurs de sortie
  FragColor = material.ambient + material.diffuse + material.specular;
  vNormal_vs = vec3(uNormal * vertexNormal);
  vPosition = vec3(uView * model * vertexPosition);
  Kd = material.diffuse.rgb;
  Ks = material.specular.rgb;
  shine = material.shininess;

  gl_Position = viewProjection * model * vec4(iVertexPosition, 1.f);
}
