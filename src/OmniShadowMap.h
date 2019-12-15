//
// Created by Yihe Wang on 2019/12/15.
//

#ifndef FINALPROJECT_OMNISHADOWMAP_H
#define FINALPROJECT_OMNISHADOWMAP_H

#include "Header.h"
#include "ShadowMap.h"

class OmniShadowMap : public ShadowMap{
public:
    OmniShadowMap();
    bool init(GLuint width, GLuint height);

    void bindFramebuffer();
    void useTexture(GLenum textureUnit);


    ~OmniShadowMap();
};


#endif //FINALPROJECT_OMNISHADOWMAP_H
