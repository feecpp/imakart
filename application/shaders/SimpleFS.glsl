#version 330
in vec3 FragColor;

uniform vec4 color;
out vec4 oFragColor;

void main(void)
{
  oFragColor = color;
}
