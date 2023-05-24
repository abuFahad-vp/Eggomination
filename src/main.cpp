
#include "../include/Renderer.h"
#include "vertexConf.h"
#include "objects.h"
#include "random.h"
#include <time.h>
#include <cstdlib>
#include <string>
#include <bits/stdc++.h>
#include <stdio.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void drawNumber(std::vector<Texture> numTex,Shader textShader, int num, float x, float y);
void readHighScore();
void writeHighScore(int score);

std::vector<int> to_digits(int n);

unsigned int vao[9],vbo[9], ebo[9];

int currentCount = 0;
int highScore;
int number_of_obj = 9;

unsigned int bg = 0;
unsigned int sprite = 1;
unsigned int motta = 2;
unsigned int press = 3;
unsigned int high = 4;
unsigned int current = 5;
unsigned int score = 6;
unsigned int times = 7;
unsigned int number = 8;

float basket_x = 0.0f;
bool start = false;
float start_time = 0.0f;

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
    glfwSetKeyCallback(window,key_callback);

    // glew initialization
    if( glewInit() != GLEW_OK ) {
        std::cout << "error" << std::endl;
        return -1;
    }
    // opengl configurations for making transparent objects    
    GCE glEnable(GL_BLEND); GCE
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); GCE


    Shader textShader(SHADER_DIR "textVertex.shader", SHADER_DIR "textFragment.shader");

    // BackGround
    Object(bg_vertices,indices,&vao[bg],&vbo[bg],&ebo[bg]);
    Shader bgShader(SHADER_DIR "bgVertex.shader", SHADER_DIR "bgFragment.shader");
    Texture bgTex(GL_TEXTURE_2D,TEX_DIR "bg.jpg",false);
    bgShader.use(); 
    bgShader.setInt("bgTex", 0);

    // press text
    Object(press_vertices,indices,&vao[press],&vbo[press],&ebo[press]);
    Texture pressTex(GL_TEXTURE_2D,TEX_DIR "pressAny.png",true);
    pressTex.parameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    pressTex.parameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // highscore text
    Object(high_vertices,indices,&vao[high],&vbo[high],&ebo[high]);
    Texture highTex(GL_TEXTURE_2D,TEX_DIR "highscore.png",true);
    pressTex.parameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    pressTex.parameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // current_score text
    Object(current_vertices,indices,&vao[current],&vbo[current],&ebo[current]);
    Texture currentTex(GL_TEXTURE_2D,TEX_DIR "currentScore.png",true);
    currentTex.parameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    currentTex.parameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // score text
    Object(score_vertices,indices,&vao[score],&vbo[score],&ebo[score]);
    Texture scoreTex(GL_TEXTURE_2D,TEX_DIR "score.png",true);
    scoreTex.parameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    scoreTex.parameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // time text
    Object(time_vertices,indices,&vao[times],&vbo[times],&ebo[times]);
    Texture timeTex(GL_TEXTURE_2D,TEX_DIR "time.png",true);
    timeTex.parameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    timeTex.parameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // number text
    Object(number_vertices,indices,&vao[number],&vbo[number],&ebo[number]);
    std::vector<Texture> numTex;
    for(int i=0;i<10;i++) {
        Texture tex(GL_TEXTURE_2D,TEX_DIR+std::to_string(i)+".png",true);
        tex.parameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        tex.parameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        numTex.push_back(tex);
    }

    // Sprite
    Object(sprite_vertices,indices,&vao[sprite],&vbo[sprite],&ebo[sprite]);
    Shader spriteShader(SHADER_DIR "spriteVertex.shader", SHADER_DIR "spriteFragment.shader");
    Texture spriteTex(GL_TEXTURE_2D,TEX_DIR "basket.png",true);
    spriteTex.parameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    spriteTex.parameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    spriteShader.use();
    spriteShader.setInt("spriteTex",0);
    float basket_y = -0.91f;

    // Motta
    Object(motta_vertices,indices,&vao[motta],&vbo[motta],&ebo[motta]);
    Shader mottaShader(SHADER_DIR "mottaVertex.shader", SHADER_DIR "mottaFragment.shader");
    Texture mottaTex(GL_TEXTURE_2D, TEX_DIR "motta.png",true);
    mottaTex.parameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    mottaTex.parameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    mottaShader.use();
    mottaShader.setInt("mottaTex",0);
    srand(time(0));
    int eggCount = 6;
    float yvalue[eggCount];
    float xvalue[eggCount];
    float speed[eggCount];

    for(int i=0;i<eggCount;i++) {

        yvalue[i] = 1.0f;
        xvalue[i] = glRandomNormalized(4);
        speed[i] =  glRandomRange(500,1500)*(0.00001);
    }

    // otherwise all of them droping together
    yvalue[eggCount-1] = 1.5f;
    yvalue[eggCount-2] = 1.2f;
    yvalue[eggCount-3] = 2.0f;

    int count = 0;
    readHighScore();
    // init time
    glfwGetTime();

    while (!glfwWindowShouldClose(window)) {

        glm::mat4 model(1.0f);
        processInput(window);
        GCE glClear(GL_COLOR_BUFFER_BIT); GCE

        // draw background
        drawObject(bgShader,bgTex,GL_TEXTURE0,&vao[bg],&ebo[bg]); 

        
        if(start) {
            if(glfwGetTime() - start_time <= 20+1) {
                // draw score card
                model = glm::mat4(1.0f);
                model = glm::translate(model,glm::vec3(-0.7f,1.2f,0.0f));
                textShader.use();
                textShader.setMat4("model",model);
                drawObject(textShader,scoreTex,GL_TEXTURE0,&vao[score],&ebo[score]);

                drawNumber(numTex,textShader,count,-0.4,1.2f);

                // draw time card
                model = glm::mat4(1.0f);
                model = glm::translate(model,glm::vec3(0.75f,1.2f,0.0f));
                textShader.use();
                textShader.setMat4("model",model);
                drawObject(textShader,timeTex,GL_TEXTURE0,&vao[times],&ebo[times]);
                drawNumber(numTex,textShader,(int)(glfwGetTime() - start_time),1.0,1.2f);
                for(int i=0;i<eggCount;i++) {

                    mottaShader.use();
                    glm::mat4 modelMotta = glm::mat4(1.0);

                    if(yvalue[i] < -1.0f) {
                        yvalue[i] = 1.0f;
                        xvalue[i] =  glRandomNormalized(4);
                        speed[i]  =  glRandomRange(500,1500)*(0.00001);
                    }

                    // if collided increment counter
                    if(yvalue[i] < basket_y+0.1 && yvalue[i] > basket_y-0.1 && xvalue[i] < basket_x+0.1 && xvalue[i] > basket_x-0.1) {
                        count += 1;
                        yvalue[i] = 1.0f;
                        xvalue[i] =  glRandomNormalized(4);
                        speed[i]  =  glRandomRange(500,1500)*(0.00001);
                    }

                    modelMotta = glm::translate(modelMotta,glm::vec3(xvalue[i],yvalue[i],0.0f));
                    mottaShader.setMat4("model",modelMotta);
                    drawObject(mottaShader,mottaTex,GL_TEXTURE0,&vao[motta],&ebo[motta]);
                    yvalue[i] -= speed[i];
                }
            
                spriteShader.use();
                glm::mat4 modelSprite(1.0);
                modelSprite = glm::translate(modelSprite,glm::vec3(basket_x,basket_y,0.0f));
                spriteShader.setMat4("model",modelSprite);
                drawObject(spriteShader,spriteTex,GL_TEXTURE0,&vao[sprite],&ebo[sprite]);
            } else {
                start = false;
            }
        }else {
            // draw press any text
            model = glm::mat4(1.0);
            model = glm::translate(model,glm::vec3(-0.05,0.65,0.0));
            float scale = 0.05*sin(5*glfwGetTime() - 1.2) + 0.95;
            model = glm::scale(model,glm::vec3(scale,scale,1.0));
            textShader.use();
            textShader.setMat4("model",model);
            drawObject(textShader,pressTex,GL_TEXTURE0,&vao[press],&ebo[press]);

            // draw highscore
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-0.7f,-0.4f,0.0f));
            textShader.use();
            textShader.setMat4("model",model);
            drawObject(textShader,highTex,GL_TEXTURE0,&vao[high],&ebo[high]);

            // draw currentscore
            model = glm::mat4(1.0);
            model = glm::translate(model, glm::vec3(0.3f,-0.4f,0.0f));
            textShader.use();
            textShader.setMat4("model",model);
            drawObject(textShader,currentTex,GL_TEXTURE0,&vao[current],&ebo[current]);
            if(count > 0) {
                currentCount = count;
                if(currentCount > highScore) {
                    highScore = currentCount;
                    writeHighScore(highScore);
                }
            }
            drawNumber(numTex,textShader,highScore,-0.2,-0.4);
            drawNumber(numTex,textShader,currentCount,0.93,-0.4);

            basket_x = 0.0f;
            count = 0;

            // reseting the game
            for(int i=0;i<eggCount;i++) {

                yvalue[i] = 1.0f;
                xvalue[i] = glRandomNormalized(4);
                speed[i] =  glRandomRange(500,1500)*(0.00001);
            }

            // otherwise all of them droping together
            yvalue[eggCount-1] = 1.5f;
            yvalue[eggCount-2] = 1.2f;
            yvalue[eggCount-3] = 2.0f;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    bgShader.deleteShader();
    spriteShader.deleteShader();
    mottaShader.deleteShader();
    textShader.deleteShader();

    deleteObject(vao,vbo,ebo,number_of_obj);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {


    if(glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS) {
        basket_x -= 0.025f;
        if(basket_x < -0.95f) basket_x = -0.95f;
    }

    if(glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS) {
        basket_x += 0.025f;
        if(basket_x > 0.95f) basket_x = 0.95f;
    }
    
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window,true);
    }
    if(key == GLFW_KEY_ENTER && action == GLFW_PRESS && !start) {
        start = true;
        start_time = glfwGetTime();
    }
};

// converts to digits
std::vector<int> to_digits(int n) {
    std::vector<int> digit;
    while(n>0) {
        digit.push_back(n%10); 
        n /= 10;
    }
    return digit;
}

void drawNumber(std::vector<Texture> numTex,Shader textShader, int num, float x, float y) {
    float offset = 0.0;
    std::vector<int> digits = to_digits(num);

    if(digits.size() < 1) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x,y,0.0f));
        textShader.use();
        textShader.setMat4("model",model);
        drawObject(textShader,numTex[0],GL_TEXTURE0,&vao[number],&ebo[number]); 
    }
    for(int i=digits.size()-1;i>=0;i--) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x+offset,y,0.0f));
        textShader.use();
        textShader.setMat4("model",model);
        drawObject(textShader,numTex[digits[i]],GL_TEXTURE0,&vao[number],&ebo[number]); 
        offset += 0.05;
    }
}
void readHighScore() {
    FILE* file = fopen("/home/abu/graphics/Eggomination/res/highscore.txt","r");
    fscanf(file,"%d",&highScore);
    fclose(file);
}

void writeHighScore(int score) {
    FILE* file = fopen("/home/abu/graphics/Eggomination/res/highscore.txt","w");
    fprintf(file,"%d",score);
}
