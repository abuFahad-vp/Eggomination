#include "../include/Renderer.h"


void Object(float* vertices, unsigned int* indices, unsigned int* vao, unsigned int* vbo, unsigned int* ebo) {

    GCE
    glGenVertexArrays(1, vao); GCE
    glGenBuffers(1, vbo); GCE
    glGenBuffers(1, ebo); GCE

    glBindVertexArray(*vao); GCE

    glBindBuffer(GL_ARRAY_BUFFER, *vbo); GCE
    glBufferData(GL_ARRAY_BUFFER, 32*sizeof(float), vertices, GL_STATIC_DRAW); GCE

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo); GCE
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), indices, GL_STATIC_DRAW); GCE

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); GCE
    glEnableVertexAttribArray(0); GCE

    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); GCE
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); GCE
    glEnableVertexAttribArray(2);

}

void drawObject(Shader bgShader,Texture bgTex,unsigned int c, unsigned int* vao, unsigned int* ebo) {
    GCE
    bgShader.use();
    glActiveTexture(c); GCE
    bgTex.use();
    glBindVertexArray(*vao); GCE
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo); GCE
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); GCE
}

void deleteObject(unsigned int* vao,unsigned int* vbo, unsigned int* ebo,int count) {
    glDeleteVertexArrays(count,vao); GCE
    glDeleteBuffers(count,vbo); GCE
    glDeleteBuffers(count,ebo); GCE
}
