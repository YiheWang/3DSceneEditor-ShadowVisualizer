#include "Light.h"

class DirectionalLight :
	public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
					GLfloat ambientIntensity, GLfloat diffuseIntensity,
					GLfloat xDirection, GLfloat yDirection, GLfloat zDirection);

	void useLight(GLfloat ambientColorLocation, GLfloat ambientIntensityLocation,
		GLfloat diffuseIntensityLocation, GLfloat directionLocation);

	~DirectionalLight();

private:
	glm::vec3 direction;
};

