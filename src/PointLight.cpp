//
// Created by Yihe Wang on 2019/12/10.
//

#include "PointLight.h"

PointLight::PointLight() : Light(){
    lightPosition = glm::vec3(0.0f, 1.0f, 0.0f);
}

PointLight::PointLight(GLuint shadowWidth, GLuint shadowHeight,
                    GLfloat nearPlane, GLfloat farPlane,
                    GLfloat red, GLfloat green, GLfloat blue,
                    GLfloat ambientIntensity, GLfloat diffuseIntensity,
                    GLfloat x, GLfloat y, GLfloat z) : Light(shadowWidth, shadowHeight, red, green, blue, ambientIntensity, diffuseIntensity){
    lightPosition = glm::vec3(x, y, z);

    this->farPlane = farPlane;
    this->nearPlane = nearPlane;
    float aspect = (float)shadowWidth / (float)shadowHeight;
    lightProjection = glm::perspective(glm::radians(90.0f), aspect, nearPlane, farPlane);

    shadowMap = new OmniShadowMap();
    shadowMap->init(shadowWidth, shadowHeight);
}

void PointLight::useLight(GLfloat lightColorLocation, GLfloat ambientIntensityLocation,
              GLfloat diffuseIntensityLocation, GLfloat lightPositionLocation)
{
    Light::useLight(lightColorLocation, ambientIntensityLocation, diffuseIntensityLocation);
    glUniform3f(lightPositionLocation, lightPosition.x, lightPosition.y, lightPosition.z);
}

std::vector<glm::mat4> PointLight::calculateLightTransform(){
    std::vector<glm::mat4> lightMatrices;
    // + x, - x
    lightMatrices.push_back(lightProjection * glm::lookAt(lightPosition, lightPosition + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    lightMatrices.push_back(lightProjection * glm::lookAt(lightPosition, lightPosition + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    // + y, -y
    lightMatrices.push_back(lightProjection * glm::lookAt(lightPosition, lightPosition + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    lightMatrices.push_back(lightProjection * glm::lookAt(lightPosition, lightPosition + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    // + z, -z
    lightMatrices.push_back(lightProjection * glm::lookAt(lightPosition, lightPosition + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    lightMatrices.push_back(lightProjection * glm::lookAt(lightPosition, lightPosition + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

    return lightMatrices;
}

void PointLight::keyControl(bool *keys, GLfloat deltaTime){
    GLfloat movedAmount = 1.0 * deltaTime;

    //move light direction of z axis
    if(keys[GLFW_KEY_UP]){
        lightPosition.z += movedAmount;
    }
    if(keys[GLFW_KEY_DOWN]){
        lightPosition.z -= movedAmount;
    }
    //move light direction of x axis
    if(keys[GLFW_KEY_LEFT]){
        lightPosition.x += movedAmount;
    }
    if(keys[GLFW_KEY_RIGHT]){
        lightPosition.x -= movedAmount;
    }
    //move light direction of y axis
    if(keys[GLFW_KEY_N]){
        lightPosition.y += movedAmount;
    }
    if(keys[GLFW_KEY_M]){
        lightPosition.y -= movedAmount;
    }
}

GLfloat PointLight::getFarPlane(){
    return farPlane;
}

glm::vec3 PointLight::getPosition(){
    return lightPosition;
}

PointLight::~PointLight(){

}