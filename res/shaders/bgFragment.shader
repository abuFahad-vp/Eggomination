
#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
in vec3 bgColor;

uniform sampler2D bgTex;

void main() {
    FragColor = texture(bgTex, TexCoord);
}