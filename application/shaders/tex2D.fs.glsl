#version 330 core

in vec2 vTexturePosition;

out vec4 fFragColor;

uniform sampler2D uTexture;

void main() {
   fFragColor = texture2D(uTexture, vTexturePosition);
};