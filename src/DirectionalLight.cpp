#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light(){
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight,
                                GLfloat red, GLfloat green, GLfloat blue,
                                GLfloat ambientIntensity, GLfloat diffuseIntensity,
                                GLfloat xDirection, GLfloat yDirection, GLfloat zDirection) : Light(shadowWidth, shadowHeight, red, green, blue, ambientIntensity, diffuseIntensity){
	direction = glm::vec3(xDirection, yDirection, zDirection);
	lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

void DirectionalLight::useLight(GLfloat lightColorLocation, GLfloat ambientIntensityLocation,
	GLfloat diffuseIntensityLocation, GLfloat directionLocation){
    Light::useLight(lightColorLocation, ambientIntensityLocation, diffuseIntensityLocation);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
}

glm::mat4 DirectionalLight::calculateLightTransform(){
    return lightProjection * glm::lookAt(-direction, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void DirectionalLight::keyControl(bool *keys, GLfloat deltaTime){
    GLfloat movedAmount = 1.0 * deltaTime;

    //move light direction of z axis
    if(keys[GLFW_KEY_UP]){
        direction.z += movedAmount;
    }
    if(keys[GLFW_KEY_DOWN]){
        direction.z -= movedAmount;
    }
    //move light direction of x axis
    if(keys[GLFW_KEY_LEFT]){
        direction.x += movedAmount;
    }
    if(keys[GLFW_KEY_RIGHT]){
        direction.x -= movedAmount;
    }
    //move light direction of y axis
    if(keys[GLFW_KEY_N]){
        direction.y += movedAmount;
    }
    if(keys[GLFW_KEY_M]){
        direction.y -= movedAmount;
    }
}

DirectionalLight::~DirectionalLight()
{
}
