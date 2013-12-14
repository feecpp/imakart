#version 330
in vec4 FragColor;

//couleur Kd --> coef reflection diffuse du materiau de l'objet
//couleur Ks --> coef reflection glossy du materiau de l'objet
//float shininess --> controlle la taille de la "tache" de brillance (en fonction du materiau de l'objet)
//vec3 N --> normal de l'objet


out vec4 oFragColor;

/*
//Calcul de la luminosite
vec3 blinnPhong() {
  vec3 wi = normalize(uLightDir_vs);
  vec3 Li = normalize(uLightIntensity);
  vec3 w0 //Vecteur qui pointe vers la camera --> or la camera bouge
  vec3 halfVector = (w0+wi)/2;

  vec3 res = Li( Kd*dot(wi,N) +  Ks*pow(dot(halfVector,N),shininess));

  return res;
}*/

void main(void)
{
  oFragColor = FragColor;
}
