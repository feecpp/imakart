#version 330
in vec2 vertexPosition;
out vec2 vTexCoord;

void main(void)
{
    gl_Position = vertexPosition;
    vTexCoord = (vertexPosition + 1) / 2.f;
}
