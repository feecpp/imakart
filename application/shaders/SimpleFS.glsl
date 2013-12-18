#version 330
in vec4 FragColor;
in vec4 vNormal_vs; //Normale de "l'objet"
in vec4 vPosition; //Position en fonction de la caméra

//////// EN RAPPORT AVEC L'OBJET //////////
in vec4 Kd; //--> coef reflection diffuse du materiau de l'objet
in vec4 Ks; //--> coef reflection glossy du materiau de l'objet
in float shine; //--> controlle la taille de la "tache" de brillance (en fonction du materiau de l'objet)


uniform mat4 model = mat4(1);
/////// EN RAPPORT AVEC LA SOURCE DE LUMIERE ////////
uniform vec3 uLightDir;
uniform vec3 uLightPos;
uniform vec3 uLi; //--> LightIntensity


out vec4 oFragColor;


//Calcul de la luminosite
vec4 blinnPhong() {
  vec4 wi = normalize(vec4(uLightDir,1.0));//Vecteur qui pointe vers la lumière
  vec4 w0 = normalize(-vPosition);//Vecteur qui pointe vers la camera
  vec4 halfVector = (w0+wi)*0.5f;

  vec4 res = vec4(uLi,1.0)*( Kd*dot(wi,vNormal_vs) +  Ks*pow(dot(halfVector,vNormal_vs),shine));

  return res;
}

vec4 blinnPhongPonctuelle(){
    vec4 wi = normalize(vec4(uLightDir,1.0)-vPosition);//Vecteur qui pointe vers la lumière
    vec4 w0 = normalize(-vPosition);//Vecteur qui pointe vers la camera
    vec4 halfVector = (w0+wi)*0.5f;
    float d = length(wi);

    vec4 res = vec4(uLi,1.0)*( Kd*dot(wi,vNormal_vs) +  Ks*pow(dot(halfVector,vNormal_vs),shine))/(d*d);

    return res;
}

void main(void)
{
  //oFragColor = FragColor;
  oFragColor = blinnPhong();
}
