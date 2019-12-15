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
    GLuint getCameraPositionLocation();
    GLuint getSpecularIntensityLocation();
    GLuint getShininessLocation();

    GLuint getPointLightColorLocation();
    GLuint getPointLightPositionLocation();
    GLuint getPointLightAmbientIntensityLocation();
    GLuint getPointLightDiffuseIntensityLocation();

    GLuint getDirectionalLightColorLocation();
    GLuint getDirectionalLightDirectionLocation();
    GLuint getDirectionalLightAmbientIntensityLocation();
    GLuint getDirectionalLightDiffuseIntensityLocation();

    GLuint getOmniLightPositionLocation();
    GLuint getFarPlaneLocation();

    void setTexture(GLuint textureUnit);
    void setDirectionalShadowMap(GLuint textureUint);
    void setDirectionalLightTransform(glm::mat4 lightTransform);

    void setOmniLightMatrices(std::vector<glm::mat4> lightMatrices);

    void useShader();
    void clearShader();
    ~Shader();

private:
    GLuint shaderID;
    GLuint uniformProjection;
    GLuint uniformModel;
    GLuint uniformView;
    GLuint uniformColor;
    GLuint uniformCameraPosition;
    GLuint uniformSpecularIntensity;
    GLuint uniformShininess;

    GLuint uniformDirectionalLightTransform;
    GLuint uniformDirectionalShadowMap;
    GLuint uniformTexture;

    GLuint uniformOmniLightPosition;
    GLuint uniformFarPlane;
    GLuint uniformOmniLightMatrices[6];

    struct {
        GLuint uniformLightColor;
        GLuint uniformLightPosition;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;
    }uniformPointLight;

    struct {
        GLuint uniformLightColor;
        GLuint uniformLightDirection;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;
    }uniformDirectionalLight;

    void compileShader(const char* vertexCode, const char* fragmentCode);
    void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};


#endif //ASSIGNMENT_3_SHADER_H
