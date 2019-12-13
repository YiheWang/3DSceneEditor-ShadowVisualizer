//
// Created by Yihe Wang on 2019/12/10.
//

#include "PointLight.h"

PointLight::PointLight() : Light(){
    lightPosition = glm::vec3(0.0f, 1.0f, 0.0f);
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue,
                    GLfloat ambientIntensity, GLfloat diffuseIntensity,
                    GLfloat x, GLfloat y, GLfloat z) : Light(1024, 1024, red, green, blue, ambientIntensity, diffuseIntensity){
    lightPosition = glm::vec3(x, y, z);
}

void PointLight::useLight(GLfloat lightColorLocation, GLfloat ambientIntensityLocation,
              GLfloat diffuseIntensityLocation, GLfloat lightPositionLocation)
{
    Light::useLight(lightColorLocation, ambientIntensityLocation, diffuseIntensityLocation);
    glUniform3f(lightPositionLocation, lightPosition.x, lightPosition.y, lightPosition.z);
}

PointLight::~PointLight(){

}