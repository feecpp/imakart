#version 330
in vec4 vNormal_vs; //Normale de "l'objet"
in vec4 vPosition_vs; //Position en fonction de la caméra
in vec2 TexCoord;

uniform sampler2D uTexture;
uniform bool isTextured = false;

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

const int MAX_PLIGHTS = 2;
uniform Point points[MAX_PLIGHTS];

struct Spot
{
  Point base;
  vec4 uLightDir;
  float uCutoff;
};
uniform Spot spot;

uniform vec4 uAmbientLight;


out vec4 oFragColor;


//Calcul directionalLight
vec4 ADS()
{
  vec4 res;

  float fDotProduct = max(0.0f, dot(vNormal_vs, normalize(directional.uLightDir)));
  vec4 vDiffuseColor = material.diffuse * vec4(directional.uLi,1.0) * fDotProduct;

  vec4 halfVector = (normalize(-vPosition_vs) + normalize(directional.uLightDir)) * 0.5f;
  float DotProduct = max(0.0f, dot(vNormal_vs,halfVector));
  float PowProduct = pow(DotProduct,material.shininess);
  vec4 vSpecularColor = material.specular * vec4(directional.uLi,1.0) * PowProduct;

  vec4 vAmbientColor = uAmbientLight * material.ambient;

  res = vAmbientColor + vDiffuseColor + vSpecularColor;

  return res;
}

//Calcul pointLight
vec4 blinnPhongPonctuelle(Point point){
  vec4 res;

  float fDotProduct = max(0.0f, dot(vNormal_vs, normalize(point.uLightPos-vPosition_vs)));
  vec4 vDiffuseColor = vec4(material.diffuse.rgb * point.uLi * fDotProduct, 1.0);
  float d = distance(normalize(point.uLightPos),normalize(vPosition_vs));

  vec4 halfVector = (normalize(-vPosition_vs)+normalize(point.uLightPos-vPosition_vs))*0.5f;
  float DotProduct = max(0.0f, dot(vNormal_vs,halfVector));
  float PowProduct = pow(DotProduct,material.shininess);
  vec4 vSpecularColor = material.specular * vec4(point.uLi,1.0) * PowProduct;

  vec4 vAmbientColor = uAmbientLight * material.ambient;

  res = (vAmbientColor + vDiffuseColor + vSpecularColor) / (d);

  return res;
}

//Calcul spotLight
vec4 CalcSpotLight() {
    vec4 res = vec4(0);
    vec4 spotDirection  = normalize(spot.uLightDir);
    float spotFactor = dot(spotDirection , normalize(spot.base.uLightPos - vPosition_vs));
    spotFactor = max(0.0f, spotFactor);
//Problème dans le calcul de l'angle spotFactor...

    if (acos(spotFactor) > spot.uCutoff ) {
        res = blinnPhongPonctuelle(spot.base);
        //res = vec4(1.f,1.f,1.f,0.f); // Pour les tests
    }else{
        res = uAmbientLight * material.ambient;
    }

    return res;
}

void main(void)
{
    vec4 TotalLight = ADS();

    for (int i = 0 ; i < MAX_PLIGHTS ; i++) {
        TotalLight += blinnPhongPonctuelle(points[i]);
   }

  if (isTextured)
  {
    oFragColor = texture(uTexture, TexCoord) * TotalLight;
  }else{
    oFragColor = TotalLight;
  }
}
