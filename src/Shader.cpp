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

void Shader::createFromFiles(const char* vertexFile, const char* geometryFile, const char* fragmentFile){
    std::string vertexString = readFile(vertexFile);
    std::string geometryString = readFile(geometryFile);
    std::string fragmentString = readFile(fragmentFile);

    const char* vertexCode = vertexString.c_str();
    //convert string to const char*
    const char* geometryCode = geometryString.c_str();
    const char* fragmentCode = fragmentString.c_str();

    compileShader(vertexCode, geometryCode, fragmentCode);
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

    compileProgram();
}

void Shader::compileShader(const char *vertexCode, const char *geometryCode, const char *fragmentCode) {
    shaderID = glCreateProgram();

    if (!shaderID)
    {
        printf("Failed to create shader\n");
        return;
    }

    addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    addShader(shaderID, geometryCode, GL_GEOMETRY_SHADER);
    addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    compileProgram();
}

void Shader::validate(){
    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s'\n", eLog);
        return;
    }
}

void Shader::compileProgram(){
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

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
    uniformColor = glGetUniformLocation(shaderID, "color");
    uniformCameraPosition = glGetUniformLocation(shaderID, "cameraPosition");
    uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
    uniformShininess = glGetUniformLocation(shaderID, "material.shininess");

    uniformPointLight.uniformLightColor = glGetUniformLocation(shaderID, "pointLight.light.lightColor");
    uniformPointLight.uniformLightPosition = glGetUniformLocation(shaderID, "pointLight.lightPosition");
    uniformPointLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "pointLight.light.ambientIntensity");
    uniformPointLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "pointLight.light.diffuseIntensity");

    uniformDirectionalLight.uniformLightColor = glGetUniformLocation(shaderID, "directionalLight.light.lightColor");
    uniformDirectionalLight.uniformLightDirection = glGetUniformLocation(shaderID, "directionalLight.lightDirection");
    uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.light.ambientIntensity");
    uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.light.diffuseIntensity");

    uniformTexture = glGetUniformLocation(shaderID, "theTexture");
    uniformDirectionalLightTransform = glGetUniformLocation(shaderID, "directionalLightTransform");
    uniformDirectionalShadowMap = glGetUniformLocation(shaderID, "directionalShadowMap");

    uniformOmniLightPosition = glGetUniformLocation(shaderID, "lightPos");
    uniformFarPlane = glGetUniformLocation(shaderID, "farPlane");
    for(int i = 0; i < 6; ++i){
        char locBuff[100] = {'\0'};
        snprintf(locBuff, sizeof(locBuff), "lightMatrices[%d]", i);
        uniformOmniLightMatrices[i] = glGetUniformLocation(shaderID, locBuff);
    }

    uniformOmniShadowMap.shadowMap = glGetUniformLocation(shaderID, "omniShadowMap.shadowMap");
    uniformOmniShadowMap.farPlane = glGetUniformLocation(shaderID, "omniShadowMap.farPlane");
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

GLuint Shader::getDirectionalLightColorLocation(){
    return uniformDirectionalLight.uniformLightColor;
}

GLuint Shader::getDirectionalLightDirectionLocation(){
    return uniformDirectionalLight.uniformLightDirection;
}

GLuint Shader::getDirectionalLightAmbientIntensityLocation(){
    return uniformDirectionalLight.uniformAmbientIntensity;
}

GLuint Shader::getDirectionalLightDiffuseIntensityLocation(){
    return uniformDirectionalLight.uniformDiffuseIntensity;
}

void Shader::setTexture(GLuint textureUnit){
    glUniform1i(uniformTexture, textureUnit);
}

void Shader::setDirectionalShadowMap(GLuint textureUnit){
    glUniform1i(uniformDirectionalShadowMap, textureUnit);
}

void Shader::setDirectionalLightTransform(glm::mat4 lightTransform){
    glUniformMatrix4fv(uniformDirectionalLightTransform, 1, GL_FALSE, glm::value_ptr(lightTransform));
}

GLuint Shader::getOmniLightPositionLocation(){
    return uniformOmniLightPosition;
}

GLuint Shader::getFarPlaneLocation(){
    return uniformFarPlane;
}

void Shader::setOmniShadowMap(GLuint textureUnit){
    glUniform1i(uniformOmniShadowMap.shadowMap, textureUnit);
}

void Shader::setFarPlane(float farPlane){
    glUniform1f(uniformOmniShadowMap.farPlane, farPlane);
}

void Shader::setOmniLightMatrices(std::vector<glm::mat4> lightMatrices){
    for(int i = 0; i < 6; ++i){
        glUniformMatrix4fv(uniformOmniLightMatrices[i], 1, GL_FALSE, glm::value_ptr(lightMatrices[i]));
    }
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