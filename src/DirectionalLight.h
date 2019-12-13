#include "Light.h"

class DirectionalLight :
	public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight,
	                GLfloat red, GLfloat green, GLfloat blue,
					GLfloat ambientIntensity, GLfloat diffuseIntensity,
					GLfloat xDirection, GLfloat yDirection, GLfloat zDirection);

	void useLight(GLfloat ambientColorLocation, GLfloat ambientIntensityLocation,
		GLfloat diffuseIntensityLocation, GLfloat directionLocation);

	glm::mat4 calculateLightTransform();

	~DirectionalLight();

private:
	glm::vec3 direction;
};

