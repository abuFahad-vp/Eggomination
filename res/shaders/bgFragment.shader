
#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D bgTex;

void main() {
    FragColor = texture(bgTex, TexCoord);
}