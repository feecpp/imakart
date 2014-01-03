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
    vec4 uLightDir;
    vec3 uLi;
};
uniform Directional directional;

struct Point
{
    vec4 uLightPos;
    vec3 uLi;
};
uniform Point point;
/*uniform int nbLights;
layout (std140) uniform Lights {
   Point light[nbLights];
}
*/

struct Spot
{
  Point base;
  vec4 uLightDir;
  float uCutoff;
};
uniform Spot spot;

uniform vec4 uAmbientLight;


out vec4 oFragColor;

//Calcul de la luminosite
vec4 ADS()
{
  float fDotProduct = max(0.0f, dot(vNormal_vs, normalize(directional.uLightDir)));
  vec4 vDiffuseColor = vec4(material.diffuse.rgb * directional.uLi * fDotProduct, 1.0);

  vec4 halfVector = (normalize(-vPosition_vs)+normalize(directional.uLightDir))*0.5f;
  float DotProduct = max(0.0f, dot(vNormal_vs,halfVector));
  float PowProduct = pow(DotProduct,material.shininess);
  vec4 vSpecularColor = vec4(material.specular.rgb * directional.uLi * PowProduct,1.0);

  vec4 vAmbientColor = vec4(0);
  if( material.ambient != vec4(0.f,0.f,0.f,1.f)){
    vAmbientColor = uAmbientLight * material.ambient;
  }

  return vAmbientColor + vDiffuseColor + vSpecularColor;
}

vec4 blinnPhongPonctuelle(Point point){
  vec4 res = vec4(0);

  float fDotProduct = max(0.0f, dot(vNormal_vs, normalize(point.uLightPos-vPosition_vs)));
  vec4 vDiffuseColor = vec4(material.diffuse.rgb * point.uLi * fDotProduct, 1.0);
  float d = length(normalize(point.uLightPos-vPosition_vs));

  vec4 halfVector = (normalize(-vPosition_vs)+normalize(point.uLightPos-vPosition_vs))*0.5f;
  float DotProduct = max(0.0f, dot(vNormal_vs,halfVector));
  float PowProduct = pow(DotProduct,material.shininess);
  vec4 vSpecularColor = vec4(material.specular.rgb * point.uLi * PowProduct,1.0);

  vec4 vAmbientColor = vec4(0);
  if( material.ambient != vec4(0.f,0.f,0.f,1.f)){
    vAmbientColor = uAmbientLight * material.ambient;
  }

  res = res +((vAmbientColor + vDiffuseColor + vSpecularColor) / (d*d));

  return res;
}

vec4 CalcSpotLight() {
    vec4 res = vec4(0);
    vec4 spotDirection  = normalize(spot.uLightDir * vNormal_vs);
    float spotFactor = max(0.0f, dot(spotDirection ,normalize(spot.base.uLightPos-vPosition_vs)));

    if (spotFactor > spot.uCutoff) {
        res = blinnPhongPonctuelle(spot.base);

    }

    return res;
}

void main(void)
{
  //oFragColor = CalcSpotLight();
    oFragColor = ADS() + blinnPhongPonctuelle(point);
  //oFragColor = material.ambient + material.diffuse + material.specular;
}
