//
// Created by Yihe Wang on 2019/11/1.
//

#include "Mesh.h"

Mesh::Mesh() {
    VAO = 0;
    VBO = 0;
    IBO = 0;
    indexCount = 0;
    meshName = "";
    model = glm::mat4(1.0f);
    //renderWay = 3;

    barycenter = glm::vec3(0.0f);
}

void Mesh::createMesh(std::vector<Vertex> vertices, std::vector<TriangleVertexIndex> indices, std::string meshName){
    indexCount = indices.size() * 3;
    barycenter = calculateBaryCenter(vertices, indices);
    this->meshName = meshName;
    this->vertices = vertices;
    this->indices = indices;
    //this->renderWay = renderWay;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), 0);
    glEnableVertexAttribArray(0); // location 0, pos
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(1); // location 1, color
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(sizeof(float) * 6));
    glEnableVertexAttribArray(2); // location 2, normal
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(sizeof(float) * 9));
    glEnableVertexAttribArray(3); // location 3, texture coordinate

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

glm::vec3 Mesh::calculateBaryCenter(std::vector<Vertex> vertices, std::vector<TriangleVertexIndex> indices){
    float totalArea = 0;
    glm::vec3 tempBarycenter(0.0f);
    for (int i = 0 ; i < indices.size(); ++i){
        unsigned int in0 = indices[i].vertexIndex1;
        unsigned int in1 = indices[i].vertexIndex2;
        unsigned int in2 = indices[i].vertexIndex3;
        glm::vec3 center;
        center[0] = (vertices[in0].x + vertices[in1].x + vertices[in2].x) / 3.0f;
        center[1] = (vertices[in0].y + vertices[in1].y + vertices[in2].y) / 3.0f;
        center[2] = (vertices[in0].z + vertices[in1].z + vertices[in2].z) / 3.0f;

        glm::vec3 v1(vertices[in1].x - vertices[in0].x,
                     vertices[in1].y - vertices[in0].y,
                     vertices[in1].z - vertices[in0].z);
        glm::vec3 v2(vertices[in2].x - vertices[in0].x,
                     vertices[in2].y - vertices[in0].y,
                     vertices[in2].z - vertices[in0].z);
        glm::vec3 normal = glm::cross(v1, v2);

        float triangleArea = 0.5f * glm::length(normal);
        tempBarycenter = tempBarycenter + triangleArea * center;
        totalArea = totalArea + triangleArea;
    }

    return (tempBarycenter / totalArea);
}


void Mesh::renderMeshWithPhongShading() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

double Mesh::findTOfRayIntersectWithMesh(glm::vec3 worldRayOrigin, glm::vec3 worldRayDirection){
    double smallestT = DBL_MAX;
    glm::vec3 rayOrigin = glm::vec3(inverse(model) * glm::vec4(worldRayOrigin, 1.0f));
    glm::vec3 rayDirection = glm::vec3(inverse(model) * glm::vec4(worldRayDirection, 0.0f));
    for(int i = 0; i < indices.size(); ++i){
        unsigned int in0 = indices[i].vertexIndex1;
        unsigned int in1 = indices[i].vertexIndex2;
        unsigned int in2 = indices[i].vertexIndex3;
        double tOfTriangle = findTOfTriangle(rayOrigin, rayDirection, vertices[in0], vertices[in1], vertices[in2]);
        if(tOfTriangle < smallestT){
            smallestT = tOfTriangle;
        }
    }
    return smallestT;
}

double Mesh::findTOfTriangle(glm::vec3 rayOrigin, glm::vec3 rayDirection, Vertex vertex1, Vertex vertex2, Vertex vertex3){
    double t;
    double u;
    double v;
    glm::mat3 A;
    glm::mat3 temp1;
    glm::mat3 temp2;
    glm::mat3 temp3;

    A = glm::mat3{
        vertex1.x - vertex2.x, vertex1.x - vertex3.x, rayDirection.x,
        vertex1.y - vertex2.y, vertex1.y - vertex3.y, rayDirection.y,
        vertex1.z - vertex2.z, vertex1.z - vertex3.z, rayDirection.z
    };

    temp1 = glm::mat3{
        vertex1.x - rayOrigin.x, vertex1.x - vertex3.x, rayDirection.x,
        vertex1.y - rayOrigin.y, vertex1.y - vertex3.y, rayDirection.y,
        vertex1.z - rayOrigin.z, vertex1.z - vertex3.z, rayDirection.z
    };

    temp2 = glm::mat3{
        vertex1.x - vertex2.x, vertex1.x - rayOrigin.x, rayDirection.x,
        vertex1.y - vertex2.y, vertex1.y - rayOrigin.y, rayDirection.y,
        vertex1.z - vertex2.z, vertex1.z - rayOrigin.z, rayDirection.z
    };

    temp3 = glm::mat3{
            vertex1.x - vertex2.x, vertex1.x - vertex3.x, vertex1.x - rayOrigin.x,
            vertex1.y - vertex2.y, vertex1.y - vertex3.y, vertex1.y - rayOrigin.y,
            vertex1.z - vertex2.z, vertex1.z - vertex3.z, vertex1.z - rayOrigin.z
    };

    t = determinant(temp3) / determinant(A);
    if (t < 0) {
        return DBL_MAX;
    }
    v = determinant(temp2) / determinant(A);
    if (v < 0 || v > 1) {
        return DBL_MAX;
    }
    u = determinant(temp1) / determinant(A);
    if (u < 0 || u > 1 - v) {
        return DBL_MAX;
    }// does not intersect with ray

    return t;
}

void Mesh::translation(float xTranslate, float yTranslate, float zTranslate){
    glm::mat4 translationModel(1.0f);
    translationModel = glm::translate(translationModel, glm::vec3(xTranslate, yTranslate, zTranslate));
    barycenter = (translationModel * glm::vec4(barycenter, 1)).xyz;
    model = translationModel * model;
}

void Mesh::translation(glm::vec3 translation){
    glm::mat4 translationModel(1.0f);
    translationModel = glm::translate(translationModel, translation);
    barycenter = (translationModel * glm::vec4(barycenter, 1)).xyz;
    model = translationModel * model;
}

void Mesh::scaling(float xScale, float yScale, float zScale){
    glm::mat4 scalingModel(1.0f);
    scalingModel = glm::scale(scalingModel, glm::vec3(xScale, yScale, zScale));
    barycenter = (scalingModel * glm::vec4(barycenter, 1)).xyz;
    model = scalingModel * model;
}

void Mesh::scaling(glm::vec3 scaling){
    glm::mat4 scalingModel(1.0f);
    scalingModel = glm::scale(scalingModel, glm::vec3(scaling));
    barycenter = (scalingModel * glm::vec4(barycenter, 1)).xyz;
    model = scalingModel * model;
}

void Mesh::rotation(float rotateAngle, int rotatingAxis){
    glm::vec3 axis(1.0f);
    if(rotatingAxis == 1){
        axis = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    else if(rotatingAxis == 2){
        axis = glm::vec3(0.0f, 1.0f, 0.0f);
    }
    else if(rotatingAxis == 3){
        axis = glm::vec3(0.0f, 0.0f, 1.0f);
    }

    glm::mat4 translateToCenter(1.0f);
    glm::mat4 rotationModel(1.0f);
    glm::mat4 translateFromCenter(1.0f);
    translateToCenter = glm::translate(translateToCenter, -barycenter);
    rotationModel = glm::rotate(rotationModel, glm::radians(rotateAngle), axis);
    translateFromCenter = glm::translate(translateFromCenter, barycenter);
    model = translateFromCenter * rotationModel * translateToCenter * model;
}

glm::vec3 Mesh::getBarycenter(){
    return barycenter;
}

glm::mat4 Mesh::getModel(){
    return model;
}

void Mesh::clearMesh(){
    if(IBO != 0){
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }
    if(VBO != 0){
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if(VAO != 0){
        glDeleteBuffers(1, &VAO);
        VAO = 0;
    }
    indexCount = 0;
}

Mesh::~Mesh(){
    clearMesh();
}