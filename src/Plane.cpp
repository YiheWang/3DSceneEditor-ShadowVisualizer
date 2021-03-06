//
// Created by Yihe Wang on 2019/12/11.
//

#include "Plane.h"

Plane::Plane(){
    planeVAO = 0;
    planeVBO = 0;
    model = glm::mat4(1.0f);
}

void Plane::createPlane(){
    GLfloat planeVertices[] = {
            // positions           //color          // normals         // texcoords
            25.0f, -0.5f,  25.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,  25.0f, 0.0f,
            -25.0f, -0.5f,  25.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
            -25.0f, -0.5f, -25.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

            25.0f, -0.5f,  25.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
            -25.0f, -0.5f, -25.0f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
            25.0f, -0.5f, -25.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
    };

    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Plane::renderPlane(){
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

Plane::~Plane(){

}
