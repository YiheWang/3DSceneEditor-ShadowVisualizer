//
// Created by Yihe Wang on 2019/12/10.
//

#ifndef FINALPROJECT_POINTLIGHT_H
#define FINALPROJECT_POINTLIGHT_H

#include "Light.h"

class PointLight : public Light{
public:
    PointLight();
    PointLight(GLfloat red, GLfloat green, GLfloat blue,
            GLfloat ambientIntensity, GLfloat diffuseIntensity,
            GLfloat x, GLfloat y, GLfloat z);

    void useLight(GLfloat lightColorLocation, GLfloat ambientIntensityLocation,
                  GLfloat diffuseIntensityLocation, GLfloat lightPositionLocation);

    ~PointLight();

private:
    glm::vec3 lightPosition;
};


#endif //FINALPROJECT_POINTLIGHT_H
