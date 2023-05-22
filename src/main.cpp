
#include "../include/Renderer.h"
#include "vertexConf.h"
#include "objects.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

float displace = 0.0f;

// settings
const unsigned int SCR_WIDTH =  960;
const unsigned int SCR_HEIGHT = 540;

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Eggomination", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glew initialization
    if( glewInit() != GLEW_OK ) {
        std::cout << "error" << std::endl;
        return -1;
    }
    
    unsigned int bg = 0;
    unsigned int sprite = 1;
    unsigned int vao[2],vbo[2], ebo[2];

    // BackGround
    Object(bg_vertices,bg_indices,&vao[bg],&vbo[bg],&ebo[bg]);
    Shader bgShader(SHADER_DIR "bgVertex.shader", SHADER_DIR "bgFragment.shader");
    Texture bgTex(GL_TEXTURE_2D,TEX_DIR "bg.jpg",false);
    bgShader.use(); 
    bgShader.setInt("bgTex", 0);

    // Sprite
    Object(sprite_vertices,sprite_indices,&vao[sprite],&vbo[sprite],&ebo[sprite]);
    Shader spriteShader(SHADER_DIR "spriteVertex.shader", SHADER_DIR "spriteFragment.shader");
    Texture spriteTex(GL_TEXTURE_2D,TEX_DIR "basket.png",true);
    spriteTex.parameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    spriteTex.parameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_BLEND); //Enable blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.

    spriteShader.use();
    spriteShader.setInt("spriteTex",0);

    while (!glfwWindowShouldClose(window)) {

        processInput(window);

        GCE glClear(GL_COLOR_BUFFER_BIT); GCE

        drawObject(bgShader,bgTex,GL_TEXTURE0,&vao[bg],&ebo[bg]);

        spriteShader.use();
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model,glm::vec3(displace,-0.9f,0.0f));
        spriteShader.setMat4("model",model);
        drawObject(spriteShader,spriteTex,GL_TEXTURE0,&vao[sprite],&ebo[sprite]);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    bgShader.deleteShader();
    spriteShader.deleteShader();

    deleteObject(&vao[bg],&vbo[bg],&ebo[bg]);
    deleteObject(&vao[sprite],&vbo[sprite],&ebo[sprite]);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {

    if(glfwGetKey(window,GLFW_KEY_ESCAPE)  == GLFW_PRESS) {
        glfwSetWindowShouldClose(window,true);
    }
    
    if(glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS) {
        displace -= 0.015f;
        if(displace < -0.9f) displace = -0.9f;
    }

    if(glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS) {
        displace += 0.015f;
        if(displace > 0.9f) displace = 0.9f;
    }
}