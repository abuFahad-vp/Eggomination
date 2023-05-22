
#include "../include/Renderer.h"
#include "background.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings
const unsigned int SCR_WIDTH = 1920/2;
const unsigned int SCR_HEIGHT = 1080/2;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glew initialization
    if( glewInit() != GLEW_OK )
        std::cout << "error" << std::endl;
    

    Shader spriteShader(SHADER_DIR "spriteVertex.shader", SHADER_DIR "spriteFragment.shader");

    float sprite_vertices[] = {
            // positions           // texture coords
            0.1f,  0.1f, 0.0f,     1.0f, 1.0f, // top right
            0.1f, -0.1f, 0.0f,     1.0f, 0.0f, // bottom right
           -0.1f, -0.1f, 0.0f,     0.0f, 0.0f, // bottom left
           -0.1f,  0.1f, 0.0f,     0.0f, 1.0f  // top left 
    };

    unsigned int sprite_indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // init background
    Background();
    Shader bgShader(SHADER_DIR "bgVertex.shader", SHADER_DIR "bgFragment.shader");
    Texture bgTex(GL_TEXTURE_2D,TEX_DIR "bg.jpg",false);
    bgShader.use(); 
    bgShader.setInt("bgTex", 0);

    // sprite
    unsigned int vao, vbo, ebo;
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    glGenBuffers(1,&ebo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sprite_vertices), sprite_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sprite_indices), sprite_indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Texture spriteTex(GL_TEXTURE_2D,TEX_DIR "container.jpg",false);
    spriteTex.parameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    spriteTex.parameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    spriteShader.use();
    spriteShader.setInt("spriteTex",0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // bg
        // bgShader.use();
        // glActiveTexture(GL_TEXTURE0);
        // bgTex.use();
        drawBackground(bgShader,bgTex,GL_TEXTURE0);

        //sprite
        spriteShader.use();
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glActiveTexture(GL_TEXTURE0);
        spriteTex.use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    bgShader.deleteShader();
    spriteShader.deleteShader();

    deleteBackground();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}