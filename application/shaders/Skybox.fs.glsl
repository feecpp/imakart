#version 330
in vec4 FragColor;
in vec3 vPosition;

out vec4 oFragColor;
uniform samplerCube cube_texture;

void main(void)
{
  oFragColor = FragColor;
  oFragColor = texture (cube_texture, vPosition);
}
