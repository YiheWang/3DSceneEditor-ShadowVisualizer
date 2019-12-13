//
// Created by Yihe Wang on 2019/11/1.
//

#ifndef ASSIGNMENT_3_MESH_H
#define ASSIGNMENT_3_MESH_H

#include "Header.h"
#include "Editor.h"

class Mesh {
public:
    Mesh();
    void createMesh(std::vector<Vertex> vertices, std::vector<TriangleVertexIndex> indices, std::string meshName);

    void translation(float xTranslate, float yTranslate, float zTranslate);
    void translation(glm::vec3 translation);
    void scaling(float xScale, float yScale, float zScale);
    void scaling(glm::vec3 scaling);
    void rotation(float rotateAngle, int rotatingAxis);

    glm::vec3 getBarycenter();
    glm::mat4 getModel();
    std::string getMeshName() {return meshName;};
    void renderMeshWithPhongShading(GLuint uniformModel, GLuint uniformColor, bool ifClicked);

    double findTOfRayIntersectWithMesh(glm::vec3 rayOrigin, glm::vec3 rayDirection);

    void clearMesh();

    ~Mesh();

private:
    std::string meshName;
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
    glm::mat4 model;
    glm::vec3 barycenter;

    std::vector<Vertex> vertices;
    std::vector<TriangleVertexIndex> indices;

    glm::vec3 calculateBaryCenter(std::vector<Vertex> vertices, std::vector<TriangleVertexIndex> indices);
    double findTOfTriangle(glm::vec3 worldRayOrigin, glm::vec3 worldRayDirection, Vertex vertex1, Vertex vertex2, Vertex vertex3);
};


#endif //ASSIGNMENT_3_MESH_H
