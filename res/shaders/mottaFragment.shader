#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
in vec3 mottaColor;

uniform sampler2D mottaTex;

void main() {
    FragColor = texture(mottaTex, vec2(TexCoord.x,TexCoord.y));
}