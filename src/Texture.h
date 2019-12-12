//
// Created by Yihe Wang on 2019/12/11.
//

#ifndef FINALPROJECT_TEXTURE_H
#define FINALPROJECT_TEXTURE_H

#include "Header.h"
#include "stb_image.h"

class Texture
{
public:
    Texture();
    Texture(char* fileLoc);

    void loadTexture();
    void useTexture();
    void disableTexture();
    void clearTexture();

    ~Texture();

private:
    GLuint textureID;
    int width, height, bitDepth;

    char* fileLocation;
};


#endif //FINALPROJECT_TEXTURE_H
