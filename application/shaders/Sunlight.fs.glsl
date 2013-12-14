#version 330 core

// Entrées du shader
in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec3 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong() {
   vec3 wi = normalize(uLightDir_vs);
   vec3 N = normalize(vNormal_vs);
   vec3 wo = normalize(-vPosition_vs);

   vec3 halfVector = 0.5f * (wi + wo);

   return uLightIntensity * (uKd * dot(wi, N) + uKs * pow(dot(halfVector, N), uShininess));
}

void main() {
        fFragColor = blinnPhong();
}
