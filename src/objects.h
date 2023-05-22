
float bg_vertices[] = {
    // positions        //color            // texture coords
    1.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,    1.0f, 1.0f, // top right
    1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // bottom right
   -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,    0.0f, 0.0f, // bottom left
   -1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 0.0f,    0.0f, 1.0f,  // top left 
};

unsigned int bg_indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

float sprite_vertices[] = {
        // positions         // color            // texture coords
        0.1f,  0.1f, 0.0f,   1.0f,0.0f,0.0f,    1.0f, 1.0f, // top right
        0.1f, -0.1f, 0.0f,   0.0f,1.0f,0.0f,    1.0f, 0.0f, // bottom right
       -0.1f, -0.1f, 0.0f,   0.0f,0.0f,1.0f,    0.0f, 0.0f, // bottom left
       -0.1f,  0.1f, 0.0f,   1.0f,1.0f,0.0f,    0.0f, 1.0f  // top left 
};

unsigned int sprite_indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

float motta_vertices[] = {
        // positions         // color            // texture coords
        0.055f,  0.1f, 0.0f,   1.0f,0.0f,0.0f,    1.0f, 1.0f, // top right
        0.055f, -0.1f, 0.0f,   0.0f,1.0f,0.0f,    1.0f, 0.0f, // bottom right
       -0.055f, -0.1f, 0.0f,   0.0f,0.0f,1.0f,    0.0f, 0.0f, // bottom left
       -0.055f,  0.1f, 0.0f,   1.0f,1.0f,0.0f,    0.0f, 1.0f  // top left 
};

unsigned int motta_indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};
