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

  vec4 res = vec4(uLi,1.0)*( material.diffuse*max(dot(wi,vNormal_vs),0.0) +  material.specular*pow(max(dot(halfVector,vNormal_vs),0.0),material.shininess) + material.ambient);

  return res;
}

vec4 BP(){
    // set the specular term to black
    vec4 spec = vec4(0.0);
    vec4 diff = vec4(0.0);
    vec4 amb = vec4(0.0);

    // normalize both input vectors
    vec3 n = normalize(vNormal_vs.rgb);
    vec3 e = normalize(-vPosition_vs.rgb);

    float intensity = max(dot(n,uLightDir), 0.0);
    //float intensity = 0.1f;

    // if the vertex is lit compute the specular color
    if (intensity > 0.0) {
        // compute the half vector
        vec3 h = normalize((uLightDir + e)*0.5f);
        // compute the specular term into spec
        float intSpec = max(dot(h,n), 0.0);
        spec = material.specular * pow(intSpec,material.shininess);
        diff = material.diffuse * max(dot(n,uLightDir), 0.0);
        amb = material.ambient * intensity;
    }

    vec4 res = max(intensity * material.diffuse + spec, material.ambient);
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
  oFragColor = ambientDiffuse();
}
