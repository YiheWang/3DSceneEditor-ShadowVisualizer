//
// Created by Yihe Wang on 2019/11/2.
//

#ifndef ASSIGNMENT_3_SHADER_H
#define ASSIGNMENT_3_SHADER_H

#include "Header.h"

class Shader {
public:
    Shader();
    void createFromString(const char* vertexCode, const char* fragmentCode);
    void createFromFiles(const char* vertexFile, const char* fragmentFile);

    std::string readFile(const char* file);

    GLuint getProjectionLocation();
    GLuint getModelLocation();
    GLuint getViewLocation();
    GLuint getColorLocation();
    GLuint getLightColorLocation();
    GLuint getLightPositionLocation();
    GLuint getAmbientIntensityLocation();
    GLuint getDiffuseIntensityLocation();
    GLuint getCameraPositionLocation();
    GLuint getSpecularIntensityLocation();
    GLuint getShininessLocation();
    GLuint getIsFlatShadingLocation();
    GLuint getTriangleNormalLocation();

    GLuint getLightDirectionLocation();

    void useShader();
    void clearShader();
    ~Shader();

private:
    GLuint shaderID;
    GLuint uniformProjection;
    GLuint uniformModel;
    GLuint uniformView;
    GLuint uniformColor;
    GLuint uniformLightColor;
    GLuint uniformLightPosition;
    GLuint uniformAmbientIntensity;
    GLuint uniformDiffuseIntensity;
    GLuint uniformCameraPosition;
    GLuint uniformSpecularIntensity;
    GLuint uniformShininess;
    GLuint uniformIsFlatShading;
    GLuint uniformTriangleNormal;

    GLuint uniformLightDirection;

    void compileShader(const char* vertexCode, const char* fragmentCode);
    void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};


#endif //ASSIGNMENT_3_SHADER_H
