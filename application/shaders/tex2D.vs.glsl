#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aTexturePosition;

out vec2 vTexturePosition;

uniform mat3 uModelMatrix;

void main() {
   vTexturePosition = aTexturePosition;
   gl_Position =  vec4(aVertexPosition.xy, 0, 1);
}
