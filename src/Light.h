//
// Created by Yihe Wang on 2019/11/15.
//

#ifndef ASSIGNMENT_3_LIGHT_H
#define ASSIGNMENT_3_LIGHT_H


#include "Header.h"

class Light {
protected:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue,
            GLfloat ambientIntensity, GLfloat diffuseIntensity);

    virtual void useLight(GLfloat lightColourLocation, GLfloat ambientIntensityLocation,
                  GLfloat diffuseIntensityLocation);

    ~Light();

protected:
    glm::vec3 lightColor;
    GLfloat ambientIntensity;
    GLfloat diffuseIntensity;
};


#endif //ASSIGNMENT_3_LIGHT_H
