//
// Created by Yihe Wang on 2019/12/11.
//

#ifndef FINALPROJECT_PLANE_H
#define FINALPROJECT_PLANE_H

#include "Header.h"

class Plane {
public:
    Plane();
    void createPlane();
    void renderPlane(GLuint uniformModel, GLuint uniformIsFlatShading, GLuint uniformColor);
    ~Plane();
private:
    GLuint planeVAO, planeVBO;
    glm::mat4 model;
};


#endif //FINALPROJECT_PLANE_H
