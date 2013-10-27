#version 330
in vec3 FragColor;

out vec4 oFragColor;

void main(void)
{
  oFragColor = vec4(FragColor , 1.0f);
}
