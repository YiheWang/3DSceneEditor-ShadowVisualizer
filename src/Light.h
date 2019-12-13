//
// Created by Yihe Wang on 2019/11/15.
//

#ifndef ASSIGNMENT_3_LIGHT_H
#define ASSIGNMENT_3_LIGHT_H


#include "Header.h"
#include "ShadowMap.h"

class Light {
protected:
    Light();
    Light(GLfloat shadowWidth, GLfloat shadowHeight,
            GLfloat red, GLfloat green, GLfloat blue,
            GLfloat ambientIntensity, GLfloat diffuseIntensity);

    virtual void useLight(GLfloat lightColourLocation, GLfloat ambientIntensityLocation,
                  GLfloat diffuseIntensityLocation);

    ShadowMap* getShadowMap() {return shadowMap;};

    ~Light();

protected:
    glm::vec3 lightColor;
    GLfloat ambientIntensity;
    GLfloat diffuseIntensity;

    glm::mat4 lightProjection;
    ShadowMap *shadowMap;
};


#endif //ASSIGNMENT_3_LIGHT_H
