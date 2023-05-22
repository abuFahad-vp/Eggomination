#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
in vec3 spriteColor;

uniform sampler2D spriteTex;

void main() {
    FragColor = texture(spriteTex, TexCoord);
}