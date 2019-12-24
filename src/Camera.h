//
// Created by Yihe Wang on 2019/11/5.
//

#ifndef Assignment_3_CAMERA_H
#define Assignment_3_CAMERA_H

#include "Header.h"

class Camera {
public:
    Camera();

    Camera(glm::vec3 startPosition, glm::vec3 startUp,
            GLfloat startAngleMoveUnit, GLfloat startMoveUnit);

    void keyControl(bool *keys, GLfloat deltaTime);
    void scrollControl(int yOffset);

    glm::vec3 getCameraPosition();
    glm::mat4 calculateViewMatrix();
    glm::vec3 getFront();

    ~Camera();

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up; // this up is different from the world up
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat angleMoveUnit;
    GLfloat moveUnit;
    GLfloat radius;
    GLfloat theta;
    GLfloat phi; // variables used for sphere coordinate

    void update();
    void updateAngle();
    void calculateSphereRadius();
    void updatePosition();
};


#endif //Assignment_3_CAMERA_H
