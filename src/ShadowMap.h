//
// Created by Yihe Wang on 2019/12/12.
//

#ifndef FINALPROJECT_SHADOWMAP_H
#define FINALPROJECT_SHADOWMAP_H

#include <cstdio>
#include "Header.h"

class ShadowMap {
public:
    ShadowMap();

    virtual bool init(GLuint width, GLuint height);

    virtual void write();
    virtual void read(GLenum textureUnit);

    GLuint getShadowWidth(){return shadowWidth;};
    GLuint getShadowHeight(){return shadowHeight;};

    ~ShadowMap();

private:
    GLuint FBO;
    GLuint shadowMap;
    GLuint shadowWidth, shadowHeight;
};


#endif //FINALPROJECT_SHADOWMAP_H
