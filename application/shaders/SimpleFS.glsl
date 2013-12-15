#version 330
in vec4 FragColor;

//////// EN RAPPORT AVEC L'OBJET //////////
//couleur Kd --> coef reflection diffuse du materiau de l'objet
//couleur Ks --> coef reflection glossy du materiau de l'objet
//float shininess --> controlle la taille de la "tache" de brillance (en fonction du materiau de l'objet)
//vec3 N --> normal de l'objet

/////// EN RAPPORT AVEC LA SOURCE DE LUMIERE ////////
//uniform vec3 uLightDir
//uniform vec3 uLi --> LightIntensity


out vec4 oFragColor;

/*
//Calcul de la luminosite
vec3 blinnPhong() {
  vec3 wi = normalize(uLightDir);
  vec3 w0 //Vecteur qui pointe vers la camera --> or la camera bouge
  vec3 halfVector = (w0+wi)/2;

  vec3 res = uLi( Kd*dot(wi,N) +  Ks*pow(dot(halfVector,N),shininess));

  return res;
}*/

void main(void)
{
  oFragColor = FragColor;
}
