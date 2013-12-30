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
uniform vec3 uLightDir;
uniform vec3 uLightPos;
uniform vec3 uLi; //--> LightIntensity


out vec4 oFragColor;

//Calcul de la luminosite
vec4 blinnPhong() {
  vec4 wi = normalize(vec4(uLightDir,1.0));//Vecteur qui pointe vers la lumiÃ¨re
  vec4 w0 = normalize(-vPosition_vs);//Vecteur qui pointe vers la camera
  vec4 halfVector = (w0+wi)*0.5f;

  vec4 res = vec4(uLi,1.0)*( material.diffuse*max(dot(wi,vNormal_vs),0.0) +  material.specular*pow(max(dot(halfVector,vNormal_vs),0.0),material.shininess) + material.ambient);

  return res;
}

vec4 ambientDiffuse()
{
  vec4 ambientLight = vec4(0.3f,0.3f,0.3f,1.f);

  float fDotProduct = max(0.0f, dot(normalize(vNormal_vs), normalize(vec4(uLightDir, 0.f))));
  vec4 vDiffuseColor = vec4(material.diffuse.rgb * uLi * fDotProduct, 1.0);
  vec4 vAmbientColor = ambientLight * material.ambient;

  return vAmbientColor + vDiffuseColor;
}

vec4 ADS()
{
    vec4 ambientLight = vec4(0.3f,0.3f,0.3f,1.f);

    float fDotProduct = max(0.0f, dot(normalize(vNormal_vs), normalize(vec4(uLightDir, 0.f))));
    vec4 vDiffuseColor = vec4(material.diffuse.rgb * uLi * fDotProduct, 1.0);

    vec4 halfVector = (normalize(-vPosition_vs)+normalize(vec4(uLightDir, 0.f)))*0.5f;
    float DotProduct = max(0.0f, dot(normalize(vNormal_vs),halfVector));
    float PowProduct = pow(DotProduct,material.shininess);
    vec4 vSpecularColor = vec4(material.specular.rgb * uLi * PowProduct,1.0);

    vec4 vAmbientColor = ambientLight * material.ambient;

    return vAmbientColor + vDiffuseColor + vSpecularColor;
}

vec4 blinnPhongPonctuelle(){
    vec4 wi = normalize(vec4(uLightPos,1.0)-vPosition_vs);//Vecteur qui pointe vers la lumière
    vec4 w0 = normalize(-vPosition_vs);//Vecteur qui pointe vers la camera
    vec4 halfVector = (w0+wi)*0.5f;
    float d = length(wi);

    vec4 res = vec4(uLi,1.0)*( material.diffuse*dot(wi,vNormal_vs) +  material.specular*pow(dot(halfVector,vNormal_vs),material.shininess) + material.ambient)/(d*d);

    return res;
}

void main(void)
{
  //oFragColor = FragColor;
  oFragColor = ADS();
}
