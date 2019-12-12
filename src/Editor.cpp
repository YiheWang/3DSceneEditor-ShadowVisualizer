//
// Created by Yihe Wang on 2019/11/14.
//

#include "Editor.h"
using namespace std;

Vertex createVertex(float x, float y, float z, float R, float G, float B,
        float normalX, float normalY, float normalZ, float texCoordX, float texCoordY){
    Vertex vertex;
    vertex.x = x; vertex.y = y; vertex.z = z;
    vertex.R = R; vertex.G = G; vertex.B = B;
    vertex.normalX = normalX;
    vertex.normalY = normalY;
    vertex.normalZ = normalZ;
    vertex.texCoordX = texCoordX;
    vertex.texCoordY = texCoordY;

    return vertex;
}

TriangleVertexIndex createVertexIndex(unsigned int vertexIndex1, unsigned int vertexIndex2, unsigned vertexIndex3){
    TriangleVertexIndex triangleVertexIndex;
    triangleVertexIndex.vertexIndex1 = vertexIndex1;
    triangleVertexIndex.vertexIndex2 = vertexIndex2;
    triangleVertexIndex.vertexIndex3 = vertexIndex3;

    return triangleVertexIndex;
}

void readOffFile(vector<TriangleVertexIndex> &indices, vector<Vertex> &vertices, string fileName){
    int indicesNum;
    int verticesNum;
    ifstream in;
    in.open(fileName);
    if (!in.is_open()) {
        cout << "File " << fileName << " open error!" << endl;
    }//check error
    else {
        cout <<fileName<<" open successful" << endl;
    }

    char line[1024] = { 0 };
    in.ignore(256, '\n');//ignore the first line

    in.getline(line, sizeof(line), '\n'); //read the second line
    stringstream word(line); //separate the second line by whitespace
    word >> verticesNum >> indicesNum;

    for (int i = 0; i < verticesNum; ++i) {
        in.getline(line, sizeof(line), '\n');//read one line
        stringstream word(line);//separate the line by whitespace
        float x, y, z;
        word >> x >> y >> z;//x, y, z
        // vertex is first vertex of triangle
        if(i % 3 == 0){
            vertices.push_back(createVertex(x, y, z, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
        }
        // vertex is second vertex of triangle
        else if(i % 3 == 1){
            vertices.push_back(createVertex(x, y, z, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));
        }
        // vertex is third vertex of triangle
        else {
            vertices.push_back(createVertex(x, y, z, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f));
        }

    }
    for (int j = 0; j < indicesNum; ++j) {
        in.getline(line, sizeof(line), '\n');//read one line
        stringstream word(line);//separate the line by whitespace
        int number;
        int vertexIndex1, vertexIndex2, vertexIndex3;
        word >> number >> vertexIndex1 >> vertexIndex2 >> vertexIndex3;
        indices.push_back(createVertexIndex(vertexIndex1, vertexIndex2, vertexIndex3));
    }

    in.close();
}

void calculatePhongShadingNormals(vector<TriangleVertexIndex> &indices, vector<Vertex> &vertices){
    for(int i = 0; i < vertices.size(); ++i){
        vertices[i].normalX = 0.0f;
        vertices[i].normalY = 0.0f;
        vertices[i].normalZ = 0.0f;
    }   // clear the normals

    for(int i = 0; i < indices.size(); ++i){
        unsigned int in0 = indices[i].vertexIndex1;
        unsigned int in1 = indices[i].vertexIndex2;
        unsigned int in2 = indices[i].vertexIndex3;
        glm::vec3 v1(vertices[in1].x - vertices[in0].x,
                     vertices[in1].y - vertices[in0].y,
                     vertices[in1].z - vertices[in0].z);
        glm::vec3 v2(vertices[in2].x - vertices[in0].x,
                     vertices[in2].y - vertices[in0].y,
                     vertices[in2].z - vertices[in0].z);
        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);

        vertices[in0].normalX += normal.x;
        vertices[in0].normalY += normal.y;
        vertices[in0].normalZ += normal.z;
        vertices[in1].normalX += normal.x;
        vertices[in1].normalY += normal.y;
        vertices[in1].normalZ += normal.z;
        vertices[in2].normalX += normal.x;
        vertices[in2].normalY += normal.y;
        vertices[in2].normalZ += normal.z;
    }   //normal bind to vertices, add the normal of different triangle together

    for(int i = 0; i < vertices.size(); ++i){
        glm::vec3 vec(vertices[i].normalX, vertices[i].normalY, vertices[i].normalZ);
        vec = glm::normalize(vec);
        vertices[i].normalX = vec[0];
        vertices[i].normalY = vec[1];
        vertices[i].normalZ = vec[2];
    }   // normalize the normal after addition
}