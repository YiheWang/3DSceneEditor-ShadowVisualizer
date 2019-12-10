//
// Created by Yihe Wang on 2019/11/15.
//

#include "Light.h"

Light::Light(){
    lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    lightPosition = glm::vec3(0.0f, 1.0f, 0.0f);
    ambientIntensity = 1.0f;
    diffuseIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue,
        GLfloat ambientIntensity, GLfloat diffuseIntensity,
        GLfloat x, GLfloat y, GLfloat z){
    lightColor = glm::vec3(red, green, blue);
    lightPosition = glm::vec3(x, y, z);
    this->ambientIntensity = ambientIntensity;
    this->diffuseIntensity = diffuseIntensity;
}

void Light::useLight(GLfloat lightColorLocation, GLfloat ambientIntensityLocation,
                     GLfloat diffuseIntensityLocation, GLfloat lightPositionLocation){
    glUniform3f(lightColorLocation, lightColor.x, lightColor.y, lightColor.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
    glUniform3f(lightPositionLocation, lightPosition.x, lightPosition.y, lightPosition.z);
}

Light::~Light(){

}