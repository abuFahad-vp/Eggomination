#include "../include/Renderer.h"

unsigned int bg_vao,bg_vbo,bg_ebo;

void Background() {

    float vertices[] = {
        // positions           // texture coords
        1.0f,  1.0f, 0.0f,    1.0f, 1.0f, // top right
        1.0f, -1.0f, 0.0f,    1.0f, 0.0f, // bottom right
       -1.0f, -1.0f, 0.0f,    0.0f, 0.0f, // bottom left
       -1.0f,  1.0f, 0.0f,    0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    GCE
    glGenVertexArrays(1, &bg_vao); GCE
    glGenBuffers(1, &bg_vbo); GCE
    glGenBuffers(1, &bg_ebo); GCE

    glBindVertexArray(bg_vao); GCE

    glBindBuffer(GL_ARRAY_BUFFER, bg_vbo); GCE
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); GCE

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bg_ebo); GCE
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); GCE

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); GCE
    glEnableVertexAttribArray(0); GCE

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); GCE
    glEnableVertexAttribArray(1);

}

void drawBackground(Shader bgShader,Texture bgTex,unsigned int c) {
    GCE
    bgShader.use();
    glActiveTexture(c); GCE
    bgTex.use();
    glBindVertexArray(bg_vao); GCE
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bg_ebo); GCE
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); GCE
}

void deleteBackground() {
    glDeleteVertexArrays(1,&bg_vao); GCE
    glDeleteBuffers(1,&bg_vbo); GCE
    glDeleteBuffers(1,&bg_ebo); GCE
}
