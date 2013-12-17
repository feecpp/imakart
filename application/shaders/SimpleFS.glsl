#version 330
in vec4 FragColor;
in vec3 vNormal_vs; //Normale de "l'objet"
in vec3 vPosition; //Position en fonction de la caméra

//////// EN RAPPORT AVEC L'OBJET //////////
in vec3 Kd; //--> coef reflection diffuse du materiau de l'objet
in vec3 Ks; //--> coef reflection glossy du materiau de l'objet
in float shine; //--> controlle la taille de la "tache" de brillance (en fonction du materiau de l'objet)


/////// EN RAPPORT AVEC LA SOURCE DE LUMIERE ////////
uniform vec3 uLightDir;
uniform vec3 uLi; //--> LightIntensity


out vec4 oFragColor;


//Calcul de la luminosite
vec4 blinnPhong() {
  vec3 wi = normalize(uLightDir);//Vecteur qui pointe vers la lumière
  vec3 w0 = normalize(-vPosition);//Vecteur qui pointe vers la camera
  vec3 halfVector = (w0+wi)*0.5f;

  vec3 light = uLi*( Kd*dot(wi,vNormal_vs) +  Ks*pow(dot(halfVector,vNormal_vs),shine));
  vec4 res = vec4(light,1.0);

  return res;
}

void main(void)
{
  //oFragColor = FragColor;
  oFragColor = blinnPhong();
}
