#version 330
in vec2 vertexPosition;
out vec2 vTexCoord;

void main(void)
{
    gl_Position = vec4(vertexPosition, 0.f, 1.f);
    vTexCoord = (vertexPosition + 1) / 2.f;
}
