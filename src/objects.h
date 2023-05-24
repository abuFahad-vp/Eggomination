#include "toNDC.h"

#define W 960
#define H 540

float bg_vertices[] = {
    // positions        //color            // texture coords
    1.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,    1.0f, 1.0f, // top right
    1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // bottom right
   -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,    0.0f, 0.0f, // bottom left
   -1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 0.0f,    0.0f, 1.0f,  // top left 
};

float sprite_vertices[] = {
        // positions         // color            // texture coords
        0.1f,  0.1f, 0.0f,   1.0f,0.0f,0.0f,    1.0f, 1.0f, // top right
        0.1f, -0.1f, 0.0f,   0.0f,1.0f,0.0f,    1.0f, 0.0f, // bottom right
       -0.1f, -0.1f, 0.0f,   0.0f,0.0f,1.0f,    0.0f, 0.0f, // bottom left
       -0.1f,  0.1f, 0.0f,   1.0f,1.0f,0.0f,    0.0f, 1.0f  // top left 
};

float motta_vertices[] = {
        // positions         // color            // texture coords
        0.055f,  0.1f, 0.0f,   1.0f,0.0f,0.0f,    1.0f, 1.0f, // top right
        0.055f, -0.1f, 0.0f,   0.0f,1.0f,0.0f,    1.0f, 0.0f, // bottom right
       -0.055f, -0.1f, 0.0f,   0.0f,0.0f,1.0f,    0.0f, 0.0f, // bottom left
       -0.055f,  0.1f, 0.0f,   1.0f,1.0f,0.0f,    0.0f, 1.0f  // top left 
};

float pressx1 = toNDC(777.412f,W);
float pressy1 = toNDC(181.831f,H);
float pressx2 = toNDC(262.381f,W);
float pressy2 = toNDC(157.764f,H);

float press_vertices[] = {
        // positions         // color            // texture coords
        pressx1, pressy1, 0.0f,   1.0f,0.0f,0.0f,    1.0f, 1.0f, // top right
        pressx1, pressy2, 0.0f,   0.0f,1.0f,0.0f,    1.0f, 0.0f, // bottom right
        pressx2, pressy2, 0.0f,   0.0f,0.0f,1.0f,    0.0f, 0.0f, // bottom left
        pressx2, pressy1, 0.0f,   1.0f,1.0f,0.0f,    0.0f, 1.0f  // top left 
};

float highx1 = toNDC(359.657f+222.783f,W);
float highy1 = toNDC(179.204f,H);
float highx2 = toNDC(359.657f,W);
float highy2 = toNDC(179.204f-39.704f,H);

float high_vertices[] = {
        // positions         // color            // texture coords
        highx1, highy1, 0.0f,   1.0f,0.0f,0.0f,    1.0f, 1.0f, // top right
        highx1, highy2, 0.0f,   0.0f,1.0f,0.0f,    1.0f, 0.0f, // bottom right
        highx2, highy2, 0.0f,   0.0f,0.0f,1.0f,    0.0f, 0.0f, // bottom left
        highx2, highy1, 0.0f,   1.0f,1.0f,0.0f,    0.0f, 1.0f  // top left 
};

float currentx1 = toNDC(359.657f+292.660f,W);
float currenty1 = toNDC(179.204f,H);
float currentx2 = toNDC(359.657f,W);
float currenty2 = toNDC(179.204f-34.560f,H);

float current_vertices[] = {
        // positions         // color            // texture coords
        currentx1, currenty1, 0.0f,   1.0f,0.0f,0.0f,    1.0f, 1.0f, // top right
        currentx1, currenty2, 0.0f,   0.0f,1.0f,0.0f,    1.0f, 0.0f, // bottom right
        currentx2, currenty2, 0.0f,   0.0f,0.0f,1.0f,    0.0f, 0.0f, // bottom left
        currentx2, currenty1, 0.0f,   1.0f,1.0f,0.0f,    0.0f, 1.0f  // top left 
};

float numberx1 = toNDC(359.657f+21.654f,W);
float numbery1 = toNDC(179.204f,H);
float numberx2 = toNDC(359.657f,W);
float numbery2 = toNDC(179.204-32.423f,H);

float number_vertices[] = {
        // positions         // color            // texture coords
       numberx1,numbery1, 0.0f,   1.0f,0.0f,0.0f,    1.0f, 1.0f, // top right
       numberx1,numbery2, 0.0f,   0.0f,1.0f,0.0f,    1.0f, 0.0f, // bottom right
       numberx2,numbery2, 0.0f,   0.0f,0.0f,1.0f,    0.0f, 0.0f, // bottom left
       numberx2,numbery1, 0.0f,   1.0f,1.0f,0.0f,    0.0f, 1.0f  // top left 
};

float scorex1 = toNDC(359.657f+130.800f,W);
float scorey1 = toNDC(179.204f,H);
float scorex2 = toNDC(359.657f,W);
float scorey2 = toNDC(179.204f-33.600f,H);

float score_vertices[] = {
        // positions         // color            // texture coords
       scorex1,scorey1, 0.0f,   1.0f,0.0f,0.0f,    1.0f, 1.0f, // top right
       scorex1,scorey2, 0.0f,   0.0f,1.0f,0.0f,    1.0f, 0.0f, // bottom right
       scorex2,scorey2, 0.0f,   0.0f,0.0f,1.0f,    0.0f, 0.0f, // bottom left
       scorex2,scorey1, 0.0f,   1.0f,1.0f,0.0f,    0.0f, 1.0f  // top left 
};

float timex1 = toNDC(359.657f+108.520f,W);
float timey1 = toNDC(179.204f,H);
float timex2 = toNDC(359.657f,W);
float timey2 = toNDC(179.204-33.600f,H);

float time_vertices[] = {
        // positions         // color            // texture coords
       timex1,timey1, 0.0f,   1.0f,0.0f,0.0f,    1.0f, 1.0f, // top right
       timex1,timey2, 0.0f,   0.0f,1.0f,0.0f,    1.0f, 0.0f, // bottom right
       timex2,timey2, 0.0f,   0.0f,0.0f,1.0f,    0.0f, 0.0f, // bottom left
       timex2,timey1, 0.0f,   1.0f,1.0f,0.0f,    0.0f, 1.0f  // top left 
};

unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

