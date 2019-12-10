//
// Created by Yihe Wang on 2019/11/15.
//

#ifndef ASSIGNMENT_3_LIGHT_H
#define ASSIGNMENT_3_LIGHT_H


#include "Header.h"

class Light {
public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue,
            GLfloat ambientIntensity, GLfloat diffuseIntensity,
            GLfloat x, GLfloat y, GLfloat z);

    void useLight(GLfloat lightColourLocation, GLfloat ambientIntensityLocation,
                  GLfloat diffuseIntensityLocation, GLfloat lightPositionLocation);

    ~Light();

private:
    glm::vec3 lightColor;
    glm::vec3 lightPosition;
    GLfloat ambientIntensity;
    GLfloat diffuseIntensity;
};


#endif //ASSIGNMENT_3_LIGHT_H
