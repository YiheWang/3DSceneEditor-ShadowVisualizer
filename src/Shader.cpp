//
// Created by Yihe Wang on 2019/11/2.
//

#include "Shader.h"

Shader::Shader(){
    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
}

void Shader::createFromString(const char *vertexCode, const char *fragmentCode) {
    compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const char* vertexFile, const char* fragmentFile){
    std::string vertexString = readFile(vertexFile);
    std::string fragmentString = readFile(fragmentFile);

    const char* vertexCode = vertexString.c_str();
    //convert string to const char*
    const char* fragmentCode = fragmentString.c_str();

    compileShader(vertexCode, fragmentCode);
}

std::string Shader::readFile(const char* file){
    std::string content;
    std::ifstream fileStream(file, std::ios::in);

    if(!fileStream.is_open()){
        std::cout<<"File open failed!"<<std::endl;
    }

    std::string line = "";
    while(!fileStream.eof()){
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

void Shader::compileShader(const char *vertexCode, const char *fragmentCode) {
    shaderID = glCreateProgram();

    if (!shaderID)
    {
        printf("Failed to create shader\n");
        return;
    }

    addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s'\n", eLog);
        return;
    }

    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s'\n", eLog);
        return;
    }

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
    uniformColor = glGetUniformLocation(shaderID, "color");
    uniformCameraPosition = glGetUniformLocation(shaderID, "cameraPosition");
    uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
    uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
    uniformIsFlatShading = glGetUniformLocation(shaderID, "isFlatShading");
    uniformTriangleNormal = glGetUniformLocation(shaderID, "triangleNormal");

    uniformPointLight.uniformLightColor = glGetUniformLocation(shaderID, "pointLight.light.lightColor");
    uniformPointLight.uniformLightPosition = glGetUniformLocation(shaderID, "pointLight.lightPosition");
    uniformPointLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "pointLight.light.ambientIntensity");
    uniformPointLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "pointLight.light.diffuseIntensity");

    uniformLightDirection = glGetUniformLocation(shaderID, "lightDirection");
}

GLuint Shader::getProjectionLocation(){
    return uniformProjection;
}

GLuint Shader::getModelLocation(){
    return uniformModel;
}

GLuint Shader::getViewLocation(){
    return uniformView;
}

GLuint Shader::getColorLocation(){
    return uniformColor;
}

GLuint Shader::getCameraPositionLocation(){
    return uniformCameraPosition;
}

GLuint Shader::getSpecularIntensityLocation(){
    return uniformSpecularIntensity;
}

GLuint Shader::getShininessLocation(){
    return uniformShininess;
}

GLuint Shader::getIsFlatShadingLocation(){
    return uniformIsFlatShading;
}
GLuint Shader::getTriangleNormalLocation(){
    return uniformTriangleNormal;
}

GLuint Shader::getPointLightColorLocation(){
    return uniformPointLight.uniformLightColor;
}

GLuint Shader::getPointLightPositionLocation(){
    return uniformPointLight.uniformLightPosition;
}

GLuint Shader::getPointLightAmbientIntensityLocation(){
    return uniformPointLight.uniformAmbientIntensity;
}

GLuint Shader::getPointLightDiffuseIntensityLocation(){
    return uniformPointLight.uniformDiffuseIntensity;
}

GLuint Shader::getLightDirectionLocation(){
    return uniformLightDirection;
}

void Shader::useShader() {
    glUseProgram(shaderID);
}

void Shader::clearShader() {
    if(shaderID != 0){
        glDeleteProgram(shaderID);
        shaderID = 0;
    }
    uniformModel = 0;
    uniformProjection = 0;
}

void Shader::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType){
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(theShader, 1024, NULL, eLog);
        fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
        return;
    }

    glAttachShader(theProgram, theShader);
}

Shader::~Shader(){
    clearShader();
}