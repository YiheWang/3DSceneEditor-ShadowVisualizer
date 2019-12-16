//
// Created by Yihe Wang on 2019/12/10.
//

#ifndef FINALPROJECT_POINTLIGHT_H
#define FINALPROJECT_POINTLIGHT_H

#include "Light.h"
#include "OmniShadowMap.h"

class PointLight : public Light{
public:
    PointLight();
    PointLight(GLuint shadowWidth, GLuint shadowHeight,
            GLfloat nearPlane, GLfloat farPlane,
            GLfloat red, GLfloat green, GLfloat blue,
            GLfloat ambientIntensity, GLfloat diffuseIntensity,
            GLfloat x, GLfloat y, GLfloat z);

    void useLight(GLfloat lightColorLocation, GLfloat ambientIntensityLocation,
                  GLfloat diffuseIntensityLocation, GLfloat lightPositionLocation);

    std::vector<glm::mat4> calculateLightTransform();

    void keyControl(bool *keys, GLfloat deltaTime);

    GLfloat getFarPlane();
    glm::vec3 getPosition();

    ~PointLight();

private:
    glm::vec3 lightPosition;

    GLfloat farPlane;
    GLfloat nearPlane;
};


#endif //FINALPROJECT_POINTLIGHT_H
