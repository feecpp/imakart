#version 330
in vec4 FragColor;
in vec4 vNormal_vs; //Normale de "l'objet"
in vec4 vPosition_vs; //Position en fonction de la caméra

//////// EN RAPPORT AVEC L'OBJET //////////
struct Material
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};
uniform Material material;

uniform mat4 model = mat4(1);
/////// EN RAPPORT AVEC LA SOURCE DE LUMIERE ////////
struct Directional
{
    vec3 uLightDir;
    vec3 uLi;
};
uniform Directional directional;

struct Point
{
    vec3 uLightPos;
    vec3 uLi;
};
uniform Point point;
uniform int nbLights;
/*
layout (std140) uniform Lights {
   Point light[nbLights];
}
*/

uniform vec4 uAmbientLight;


out vec4 oFragColor;

//Calcul de la luminosite
vec4 ADS()
{
  float fDotProduct = max(0.0f, dot(normalize(vNormal_vs), normalize(vec4(directional.uLightDir, 0.f))));
  vec4 vDiffuseColor = vec4(material.diffuse.rgb * directional.uLi * fDotProduct, 1.0);

  vec4 halfVector = (normalize(-vPosition_vs)+normalize(vec4(directional.uLightDir, 0.f)))*0.5f;
  float DotProduct = max(0.0f, dot(normalize(vNormal_vs),halfVector));
  float PowProduct = pow(DotProduct,material.shininess);
  vec4 vSpecularColor = vec4(material.specular.rgb * directional.uLi * PowProduct,1.0);

  vec4 vAmbientColor = uAmbientLight * material.ambient;

  return vAmbientColor + vDiffuseColor + vSpecularColor;
}

vec4 blinnPhongPonctuelle(){
    vec4 res =vec4(0);
  //for (int index = 0; index < nbLights; ++index)
  //{
  float fDotProduct = max(0.0f, dot(normalize(vNormal_vs), normalize(vec4(point.uLightPos, 0.f)-vPosition_vs)));
  vec4 vDiffuseColor = vec4(material.diffuse.rgb * point.uLi * fDotProduct, 1.0);
  float d = length(normalize(vec4(point.uLightPos, 0.f)-vPosition_vs));

  vec4 halfVector = (normalize(-vPosition_vs)+normalize(vec4(point.uLightPos, 0.f)-vPosition_vs))*0.5f;
  float DotProduct = max(0.0f, dot(normalize(vNormal_vs),halfVector));
  float PowProduct = pow(DotProduct,material.shininess);
  vec4 vSpecularColor = vec4(material.specular.rgb * point.uLi * PowProduct,1.0);

  vec4 vAmbientColor = uAmbientLight * material.ambient;

  res = res +((vAmbientColor + vDiffuseColor + vSpecularColor) / (d*d));
 //}

  return res;
}

void main(void)
{
  //oFragColor = FragColor;
  oFragColor = ADS() + blinnPhongPonctuelle();
}
