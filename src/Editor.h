//
// Created by Yihe Wang on 2019/11/14.
//

#ifndef ASSIGNMENT_3_EDITOR_H
#define ASSIGNMENT_3_EDITOR_H

#include "Header.h"

typedef struct Vertex{
    float x, y, z;
    float R, G, B;
    float normalX, normalY, normalZ;
}Vertex;

Vertex createVertex(float x, float y, float z, float R, float G, float B, float normalX, float normalY, float normalZ);

typedef struct TriangleVertexIndex{
    unsigned int vertexIndex1;
    unsigned int vertexIndex2;
    unsigned int vertexIndex3;
}TriangleVertexIndex;

TriangleVertexIndex createVertexIndex(unsigned int vertexIndex1, unsigned int vertexIndex2, unsigned vertexIndex3);

void readOffFile(std::vector<TriangleVertexIndex> &indices, std::vector<Vertex> &vertices, std::string fileName);

void calculatePhongShadingNormals(std::vector<TriangleVertexIndex> &indices, std::vector<Vertex> &vertices);

#endif //ASSIGNMENT_3_EDITOR_H
