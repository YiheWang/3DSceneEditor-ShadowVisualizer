//
// Created by Yihe Wang on 2019/12/15.
//

#include "OmniShadowMap.h"


OmniShadowMap::OmniShadowMap() : ShadowMap(){

}

bool OmniShadowMap::init(GLuint width, GLuint height) {
    shadowWidth = width;
    shadowHeight = height;

    glGenFramebuffers(1, &FBO);
    glGenTextures(1, &shadowMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMap);

    for(int i = 0; i < 6 ; ++i){
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
                     nullptr);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if(status != GL_FRAMEBUFFER_COMPLETE){
        printf("Framebuffer error: %i\n", status);
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return true;
}

void OmniShadowMap::bindFramebuffer(){
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void OmniShadowMap::useTexture(GLenum textureUnit){
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMap);
}


OmniShadowMap::~OmniShadowMap(){

}
