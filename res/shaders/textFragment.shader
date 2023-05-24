
#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
in vec3 textColor;

uniform sampler2D textTex;

void main() {
    FragColor = texture(textTex, TexCoord);
}