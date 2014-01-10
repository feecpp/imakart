#version 330

uniform sampler2D textureUnit0;

in vec2 vTexCoord;

void main(void)
{
  gl_FragColor = texture(textureUnit0, vTexCoord);
}
