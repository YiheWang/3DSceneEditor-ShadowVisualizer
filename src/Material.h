//
// Created by Yihe Wang on 2019/11/15.
//

#ifndef ASSIGNMENT_3_MATERIAL_H
#define ASSIGNMENT_3_MATERIAL_H


#include "Header.h"

class Material {
public:
    Material();
    Material(GLfloat specularIntensity, GLfloat shininess);
    ~Material();

    void useMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);

private:
    GLfloat specularIntensity;
    GLfloat shininess;
};


#endif //ASSIGNMENT_3_MATERIAL_H
