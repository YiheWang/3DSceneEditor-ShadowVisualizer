//
// Created by Yihe Wang on 2019/11/15.
//

#include "Light.h"

Light::Light(){
    lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    ambientIntensity = 1.0f;
    diffuseIntensity = 0.0f;
}

Light::Light(GLfloat shadowWidth, GLfloat shadowHeight,
        GLfloat red, GLfloat green, GLfloat blue,
        GLfloat ambientIntensity, GLfloat diffuseIntensity){
    shadowMap = new ShadowMap();
    shadowMap->init(shadowWidth, shadowHeight);

    lightColor = glm::vec3(red, green, blue);
    this->ambientIntensity = ambientIntensity;
    this->diffuseIntensity = diffuseIntensity;
}

void Light::useLight(GLfloat lightColorLocation, GLfloat ambientIntensityLocation,
                     GLfloat diffuseIntensityLocation){
    glUniform3f(lightColorLocation, lightColor.x, lightColor.y, lightColor.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

Light::~Light(){

}