//
// Created by Yihe Wang on 2019/12/12.
//

#include "ShadowMap.h"


ShadowMap::ShadowMap(){
    FBO = 0;
    shadowMap = 0;
}

bool ShadowMap::init(GLuint width, GLuint height){
    shadowWidth = width;
    shadowHeight = height;

    glGenFramebuffers(1, &FBO);
    glGenTextures(1, &shadowMap);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    // all the thing exceed border will be border color
    float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    //connect framebuffer with texture
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);

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

void ShadowMap::bindFramebuffer(){
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void ShadowMap::unBindFramebuffer(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMap::useTexture(GLenum textureUnit){
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
}

ShadowMap::~ShadowMap(){
    if(FBO){
        glDeleteFramebuffers(1, &FBO);
    }
    if(shadowMap){
        glDeleteTextures(1, &shadowMap);
    }
}







