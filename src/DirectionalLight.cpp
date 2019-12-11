#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light(){
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
                                GLfloat ambientIntensity, GLfloat diffuseIntensity,
                                GLfloat xDirection, GLfloat yDirection, GLfloat zDirection) : Light(red, green, blue, ambientIntensity, diffuseIntensity){
	direction = glm::vec3(xDirection, yDirection, zDirection);
}

void DirectionalLight::useLight(GLfloat lightColorLocation, GLfloat ambientIntensityLocation,
	GLfloat diffuseIntensityLocation, GLfloat directionLocation){
    Light::useLight(lightColorLocation, ambientIntensityLocation, diffuseIntensityLocation);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
}

DirectionalLight::~DirectionalLight()
{
}
