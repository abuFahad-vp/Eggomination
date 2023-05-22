
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Renderer.h"

class Texture
{
public:
    unsigned int ID;
    GLenum Target;

    Texture(GLenum Target,std::string texPath,bool isTransparent){
        unsigned int rgb = GL_RGB;
        if(isTransparent) rgb = GL_RGBA;
        this->Target = Target;
        GCE
        glGenTextures(1,&ID); GCE
        glBindTexture(Target,ID); GCE
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(texPath.c_str(), &width,&height,&nrChannels,0);
        if (data) {
            glTexImage2D(Target, 0, rgb, width, height, 0, rgb, GL_UNSIGNED_BYTE, data); GCE
            glGenerateMipmap(Target); GCE
        }else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        glBindTexture(Target,0); GCE
    }

    void use() {
        GCE glBindTexture(Target, ID); GCE
    }

    void parameteri(GLenum pname,GLint param) {
        GCE use(); GCE
        glTexParameteri(Target,pname,param); GCE
    }

};
#endif
