#version 330
in vec4 FragColor;
in vec3 vNormal_vs; //Normale de "l'objet"
in vec3 vPosition; //

//////// EN RAPPORT AVEC L'OBJET //////////
in vec3 Kd; //--> coef reflection diffuse du materiau de l'objet
in vec3 Ks; //--> coef reflection glossy du materiau de l'objet
//float shininess; --> controlle la taille de la "tache" de brillance (en fonction du materiau de l'objet)


/////// EN RAPPORT AVEC LA SOURCE DE LUMIERE ////////
uniform vec3 uLightDir;
uniform vec3 uLi; //--> LightIntensity


out vec4 oFragColor;


//Calcul de la luminosite
vec4 blinnPhong() {
  vec3 wi = normalize(uLightDir);
  vec3 w0 = normalize(-vPosition);//Vecteur qui pointe vers la camera --> or la camera bouge
  vec3 halfVector = (w0+wi)/2;

  float shininess = 16;

  vec3 light = uLi*( Kd*dot(wi,vNormal_vs) +  Ks*pow(dot(halfVector,vNormal_vs),shininess));
  vec4 res = vec4(light,1.0);

  return res;
}

void main(void)
{
  oFragColor = FragColor;
}
