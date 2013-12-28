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
  vec4 wi = normalize(vec4(uLightDir,1.0));//Vecteur qui pointe vers la lumière
  vec4 w0 = normalize(-vPosition_vs);//Vecteur qui pointe vers la camera
  vec4 halfVector = (w0+wi)*0.5f;

  vec4 res = vec4(uLi,1.0)*( material.diffuse*dot(wi,vNormal_vs) +  material.specular*pow(dot(halfVector,vNormal_vs),material.shininess) + material.ambient);

  return res;
}

vec4 ambientDiffuse()
{
  vec4 ambientLight = vec4(1);

  float fDotProduct = max(0.0f, dot(normalize(vNormal_vs), normalize(vec4(uLightDir, 0.f))));
  vec4 vDiffuseColor = vec4(material.diffuse.rgb * uLi * fDotProduct, 1.0);
  vec4 vAmbientColor = ambientLight * material.ambient;

  return vAmbientColor + vDiffuseColor;
}

vec4 ADS()
{
    // Dot product gives us diffuse intensity
    float diff = max(0.0, dot(normalize(vNormal_vs),normalize(vec4(uLightDir, 0.f))));
    // Multiply intensity by diffuse color, force alpha to 1.0
    vec4 res = diff * material.diffuse;
    // Add in ambient light
    res += material.ambient;
    // Specular Light
    vec4 vReflection = normalize(reflect(-normalize(vec4(uLightDir, 0.f)),normalize(vNormal_vs)));
    float spec = max(0.0, dot(normalize(vNormal_vs), vReflection));
    // If the diffuse light is zero, don’t even bother with the pow function
    if(diff != 0) {
        float fSpec = pow(spec, 128.0);
        res.rgb += vec3(fSpec, fSpec, fSpec);
    }
    return res;
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
