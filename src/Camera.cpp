//
// Created by Yihe Wang on 2019/11/5.
//

#include "Camera.h"
#include "Constant.h"

Camera::Camera(){

}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp,
        GLfloat startAngleMoveUnit, GLfloat startMoveUnit){
    position = startPosition;
    worldUp = startUp;

    // move one unit per time when pressing key
    angleMoveUnit = startAngleMoveUnit;
    moveUnit = startMoveUnit;
    //calculate initial radius, theta and phi
    updateAngle();
    update();
}

void Camera::scrollControl(int yOffset){
    radius = radius + (float)yOffset * 0.2;
    if(radius < 0.01f){
        radius = 0.1f;
    }
    updatePosition();
    // move camera close or far by scroll control
}

void Camera::keyControl(bool *keys, GLfloat deltaTime){
    GLfloat movedAngle = angleMoveUnit * deltaTime;
    GLfloat movedAmount = moveUnit * deltaTime;
    //moved angle in radians

    //sphere coordinates
    if(keys[GLFW_KEY_W]){
        theta = theta - movedAngle;
        if(theta < 0){
            theta = 0.01f;
        }
        updatePosition();
        update();
    }
    if(keys[GLFW_KEY_S]){
        theta = theta + movedAngle;
        if(theta > PI){
            theta = PI;
        }
        updatePosition();
        update();
    }
    if(keys[GLFW_KEY_A]){
        phi = phi - movedAngle;
        if(phi < 0){
            phi = phi + 2 * PI;
        }
        updatePosition();
        update();
    }
    if(keys[GLFW_KEY_D]){
        phi = phi + movedAngle;
        if(phi > 2 * PI){
            phi = phi - 2 * PI;
        }
        updatePosition();
        update();
    }
    if(keys[GLFW_KEY_Q]){
        radius = radius + movedAmount;
        updatePosition();
    }
    if(keys[GLFW_KEY_E]){
        radius = radius - movedAmount;
        if(radius < 0.01f){
            radius = 0.1f;
        }
        updatePosition();
    }// move on z axis
}

void Camera::updatePosition(){
    position[0] = radius * sin(theta) * sin(phi);
    position[1] = radius * cos(theta);
    position[2] = radius * sin(theta) * cos(phi);
}

glm::mat4 Camera::calculateViewMatrix(){
    // center is the object you look at
    return glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), up);
}

glm::vec3 Camera::getCameraPosition(){
    return position;
}

glm::vec3 Camera::getFront() {
    return glm::normalize(glm::vec3(0.0f) - position);
}

void Camera::calculateSphereRadius(){
    radius = glm::length(position);
}

void Camera::update(){
    front = glm::vec3(0.0f, 0.0f, 0.0f) - position;
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::updateAngle(){
    calculateSphereRadius();
    theta = acos(position[1] / radius);
    phi = atan(position[0] / position[2]);
}

Camera::~Camera(){

}