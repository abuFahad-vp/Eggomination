
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 mottaColor;
out vec4 pos;

uniform mat4 model;
uniform mat4 init;

void main() {
    pos = model * vec4(aPos,1.0);
    gl_Position = pos;
    TexCoord = aTexCoord;
    mottaColor = aColor;
}