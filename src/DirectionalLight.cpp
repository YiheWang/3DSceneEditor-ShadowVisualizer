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

DirectionalLight::~DirectionalLight()
{
}
