#include <iostream>

#include "Header.h"
#include "Editor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Plane.h"
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

const GLint WIDTH = 1200;
const GLint HEIGHT = 800;
GLint bufferWidth = 0;
GLint bufferHeight = 0;


//Window mainWindow;
Camera camera;
PointLight pointLight;
DirectionalLight directionalLight;
Material material;
Plane plane;
Texture brickTexture;

vector<Mesh*> meshList;
vector<Shader> shaderList;
Shader directionalShadowShader;
Shader omniShadowShader;

vector<TriangleVertexIndex> indicesOfBunny;
vector<Vertex> verticesOfBunny;
vector<TriangleVertexIndex> indicesOfBumpyCube;
vector<Vertex> verticesOfBumpyCube;
vector<TriangleVertexIndex> indicesOfUnitCube;
vector<Vertex> verticesOfUnitCube;

glm::mat4 projection(1.0f);
glm::mat4 view(1.0f);
glm::mat4 model(1.0f);

GLuint uniformProjection = 0;
GLuint uniformModel = 0;
GLuint uniformColor = 0;
GLuint uniformView = 0;
GLuint uniformCameraPosition = 0;
GLuint uniformShininess = 0;
GLuint uniformSpecularIntensity = 0;

GLuint uniformOmniLightPosition = 0;
GLuint uniformFarPlane = 0;

struct UniformPointLight{
    GLuint uniformLightColor = 0;
    GLuint uniformLightPosition = 0;
    GLuint uniformAmbientIntensity = 0;
    GLuint uniformDiffuseIntensity = 0;
}uniformPointLight;

struct UniformDirectionalLight{
    GLuint uniformLightColor = 0;
    GLuint uniformLightDirection = 0;
    GLuint uniformAmbientIntensity = 0;
    GLuint uniformDiffuseIntensity = 0;
}uniformDirectionalLight;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

bool keys[1024];
bool ifControlDirectionalLight = true;

int mouseClickMeshIndex = -1;

// Vertex Shader
static const char* vShader = "../Shader/vertexShader.txt";
//fragment shader
static const char* fShader = "../Shader/fragmentShader.txt";

static const char* directionalShadowMapVShader = "../Shader/directionalShadowMapVertexShader.txt";
static const char* directionalShadowMapFShader = "../Shader/directionalShadowMapFragmentShader.txt";

static const char* omniShadowMapVShader = "../Shader/omniShadowMapVertexShader.txt";
static const char* omniShadowMapGShader = "../Shader/omniShadowMapGeometryShader.txt";
static const char* omniShadowMapFShader = "../Shader/omniShadowMapFragmentShader.txt";

string bumpyCube = "../meshFile/bumpy_cube.off";
string bunny = "../meshFile/bunny.off";
string unitCube = "../meshFile/unit_cube.off";

void framebufferSize(GLFWwindow* window, int width, int height);
void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
void handleMouseButton(GLFWwindow* window, int button, int action, int mods);
static void cursorPosition(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

void createShaders();
void loadFile();
void renderObjects();
void renderDepthMapOfPointLight();
void renderDepthCubeOfDirectionalLight();
void renderScene();

int main()
{
    //mainWindow = Window(1200, 800);
    //mainWindow.Initialize();
    for (int i = 0; i < 1024; i++){
        keys[i] = false;
    } // initialize keys

    GLFWwindow* mainWindow;
    // Initialise GLFW
    if (!glfwInit())
    {
        printf("GLFW initialisation failed!");
        glfwTerminate();
        return 1;
    }

    // Setup GLFW window properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow Forward Compatbility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create the window
    mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Shadow Visualizer Window", NULL, NULL);
    if (!mainWindow)
    {
        printf("GLFW window creation failed!");
        glfwTerminate();
        return 1;
    }

    // Get Buffer Size information
    //int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    //handle current context
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetMouseButtonCallback(mainWindow, handleMouseButton);
    glfwSetFramebufferSizeCallback(mainWindow, framebufferSize);
    glfwSetCursorPosCallback(mainWindow, cursorPosition);
    glfwSetScrollCallback(mainWindow, scrollCallback);
    //glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        printf("GLEW initialisation failed!");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }
    glEnable(GL_DEPTH_TEST);

    // Setup Viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    createShaders();
    loadFile();
    //createObjects();
    plane.createPlane();
    brickTexture = Texture("../Texture/brick.png");
    brickTexture.loadTexture();

    camera = Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f),
            0.872665f, 1.0f); // move 10 degree every time unit

    material = Material(1.0f, 132);
    pointLight = PointLight(1024, 1024,
                  0.01f, 100.0f,
                  1.0f, 1.0f, 1.0f,
                  0.1f, 0.6f,
                  -3.0f, 3.0f, -3.0f);
    directionalLight = DirectionalLight(2048, 2048,
            1.0f, 1.0f, 1.0f,
            0.1f, 0.6f,
            1.0f, -1.0f, -3.0f);

    float ratio = (float)bufferWidth / (float)bufferHeight;
    //projection = glm::ortho(-1.0f * ratio, 1.0f * ratio, -1.0f, 1.0f, 0.1f, 100.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)bufferWidth/(float)bufferHeight, 0.1f, 100.0f);
    //  field of view in y direction,  aspect, near and far

    // Loop until window closed
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Get + Handle user input events
        glfwPollEvents();

        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        camera.keyControl(keys, deltaTime);
        if(ifControlDirectionalLight){
            directionalLight.keyControl(keys, deltaTime);
        }
        else {
            pointLight.keyControl(keys, deltaTime);
        }

        view = camera.calculateViewMatrix();
        //update global view, for mouse picking

        renderDepthMapOfPointLight();
        renderDepthCubeOfDirectionalLight();
        renderScene();

        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }

    return 0;
}

void framebufferSize(GLFWwindow* window, int width, int height){
    bufferWidth = width;
    bufferHeight = height;
    glViewport(0, 0, width, height);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
    camera.scrollControl(yoffset);
}

void handleKeys(GLFWwindow* window, int key, int code, int action, int mode){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    switch (key){
        case GLFW_KEY_1:
            if(action == GLFW_PRESS){
                Mesh *mesh = new Mesh();
                mesh->createMesh(verticesOfUnitCube, indicesOfUnitCube, "UnitCube");
                meshList.push_back(mesh);
            }
            break;
        case GLFW_KEY_2:
            if(action == GLFW_PRESS){
                Mesh *mesh = new Mesh();
                mesh->createMesh(verticesOfBumpyCube, indicesOfBumpyCube, "BumpyCube");
                mesh->translation(-mesh->getBarycenter());
                mesh->scaling(0.15f, 0.15f, 0.15f);
                meshList.push_back(mesh);
            }
            break;
        case GLFW_KEY_3:
            if(action == GLFW_PRESS){
                Mesh *mesh = new Mesh();
                mesh->createMesh(verticesOfBunny, indicesOfBunny, "Bunny");
                mesh->translation(-mesh->getBarycenter());
                mesh->scaling(6.0f, 6.0f, 6.0f);
                meshList.push_back(mesh);
            }
            break;

        // for light moveing
        case GLFW_KEY_UP:
            if(action == GLFW_PRESS){
                keys[key] = true;
            }
            else if(action == GLFW_RELEASE){
                keys[key] = false;
            }
            break;
        case GLFW_KEY_DOWN:
            if(action == GLFW_PRESS){
                keys[key] = true;
            }
            else if(action == GLFW_RELEASE){
                keys[key] = false;
            }
            break;
        case GLFW_KEY_LEFT:
            if(action == GLFW_PRESS){
                keys[key] = true;
            }
            else if(action == GLFW_RELEASE){
                keys[key] = false;
            }
            break;
        case GLFW_KEY_RIGHT:
            if(action == GLFW_PRESS){
                keys[key] = true;
            }
            else if(action == GLFW_RELEASE){
                keys[key] = false;
            }
            break;
        case GLFW_KEY_N:
            if(action == GLFW_PRESS){
                keys[key] = true;
            }
            else if(action == GLFW_RELEASE){
                keys[key] = false;
            }
            break;
        case GLFW_KEY_M:
            if(action == GLFW_PRESS){
                keys[key] = true;
            }
            else if(action == GLFW_RELEASE){
                keys[key] = false;
            }
            break;

            //for camera control, sphere coordinate
        case GLFW_KEY_W:
            if(action == GLFW_PRESS){
                keys[key] = true;
            }
            else if(action == GLFW_RELEASE){
                keys[key] = false;
            }
            break;
        case GLFW_KEY_S:
            if(action == GLFW_PRESS){
                keys[key] = true;
            }
            else if(action == GLFW_RELEASE){
                keys[key] = false;
            }
            break;
        case GLFW_KEY_A:
            if(action == GLFW_PRESS){
                keys[key] = true;
            }
            else if(action == GLFW_RELEASE){
                keys[key] = false;
            }
            break;
        case GLFW_KEY_D:
            if(action == GLFW_PRESS){
                keys[key] = true;
            }
            else if(action == GLFW_RELEASE){
                keys[key] = false;
            }
            break;
        case GLFW_KEY_Q:
            if(action == GLFW_PRESS){
                keys[key] = true;
            }
            else if(action == GLFW_RELEASE){
                keys[key] = false;
            }
            break;
        case GLFW_KEY_E:
            if(action == GLFW_PRESS){
                keys[key] = true;
            }
            else if(action == GLFW_RELEASE){
                keys[key] = false;
            }
            break;

            //for mesh translation
        case GLFW_KEY_G:
            if(action == GLFW_PRESS){
                if(mouseClickMeshIndex != -1){
                    meshList[mouseClickMeshIndex]->translation(0.2f, 0.0f, 0.0f);
                }
            }
            break;
        case GLFW_KEY_F:
            if(action == GLFW_PRESS){
                if(mouseClickMeshIndex != -1){
                    meshList[mouseClickMeshIndex]->translation(-0.2f, 0.0f, 0.0f);
                }
            }
            break;
        case GLFW_KEY_H:
            if(action == GLFW_PRESS){
                if(mouseClickMeshIndex != -1){
                    meshList[mouseClickMeshIndex]->translation(0.0f, 0.2f, 0.0f);
                }
            }
            break;
        case GLFW_KEY_J:
            if(action == GLFW_PRESS){
                if(mouseClickMeshIndex != -1){
                    meshList[mouseClickMeshIndex]->translation(0.0f, -0.2f, 0.0f);
                }
            }
            break;
        case GLFW_KEY_K:
            if(action == GLFW_PRESS){
                if(mouseClickMeshIndex != -1){
                    meshList[mouseClickMeshIndex]->translation(0.0f, 0.0f, 0.2f);
                }
            }
            break;
        case GLFW_KEY_L:
            if(action == GLFW_PRESS){
                if(mouseClickMeshIndex != -1){
                    meshList[mouseClickMeshIndex]->translation(0.0f, 0.0f, -0.2f);
                }
            }
            break;

            //scale up and down
        case GLFW_KEY_EQUAL:
            if(action == GLFW_PRESS){
                if(mouseClickMeshIndex != -1){
                    meshList[mouseClickMeshIndex]->scaling(1.1f, 1.1f, 1.1f);
                }
            }
            break;
        case GLFW_KEY_MINUS:
            if(action == GLFW_PRESS){
                if(mouseClickMeshIndex != -1){
                    meshList[mouseClickMeshIndex]->scaling(0.9f, 0.9f, 0.9f);
                }
            }
            break;

            //rotating around axis
        case GLFW_KEY_X:
            if(action == GLFW_PRESS){
                if(mouseClickMeshIndex != -1){
                    meshList[mouseClickMeshIndex]->rotation(20.0f, 1);
                }
            }
            break;
        case GLFW_KEY_Y:
            if(action == GLFW_PRESS){
                if(mouseClickMeshIndex != -1){
                    meshList[mouseClickMeshIndex]->rotation(20.0f, 2);
                }
            }
            break;
        case GLFW_KEY_Z:
            if(action == GLFW_PRESS){
                if(mouseClickMeshIndex != -1){
                    meshList[mouseClickMeshIndex]->rotation(20.0f, 3);
                }
            }
            break;

        case GLFW_KEY_P:
            if(action == GLFW_PRESS){
                ifControlDirectionalLight = !ifControlDirectionalLight;
                if(ifControlDirectionalLight){
                    std::cout<<"Control directional light"<<std::endl;
                }
                else {
                    std::cout<<"Control point light"<<std::endl;
                }
            }
            break;

            //delete mesh
        case GLFW_KEY_DELETE:
            if(action == GLFW_PRESS){
                if(mouseClickMeshIndex != -1){
                    free(meshList[mouseClickMeshIndex]);
                    auto triangleIndex = meshList.begin() + mouseClickMeshIndex;
                    meshList.erase(triangleIndex);
                    mouseClickMeshIndex = -1;
                }
            }
            break;
    }
}

static void cursorPosition(GLFWwindow* window, double xpos, double ypos){

}

void handleMouseButton(GLFWwindow* window, int button, int action, int mods){
    // Get the position of the mouse in the window
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // Get the size of the window
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // Convert screen position to world coordinates

    glm::vec4 ray_clip((xpos / width) * 2 - 1.0f, 1.0f - (ypos / height) * 2, -1.0f, 1.0f);
    glm::vec4 ray_eye = inverse(projection) * ray_clip;
    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);
    //glm::vec3 ray_world = (inverse(view) * ray_eye).xyz;
    glm::vec3 ray_world = glm::vec3(inverse(view) * ray_eye);
    ray_world = normalize(ray_world);

    // Update the position of the first vertex if the left button is pressed
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        double smallestT = DBL_MAX;
        for (int i = 0; i < meshList.size(); ++i){
            double tOfMesh;
            tOfMesh = meshList[i]->findTOfRayIntersectWithMesh(camera.getCameraPosition(), ray_world);
            if(tOfMesh < smallestT){
                mouseClickMeshIndex = i;
                smallestT = tOfMesh;
            } //when t of two meshes equal ,take the front one in meshList
        }
        //mouseClickMeshIndex = 2;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        mouseClickMeshIndex = -1;
        //reset mesh index
    }
}

void createShaders(){
    Shader *shader1 = new Shader();
    shader1->createFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);

    directionalShadowShader = Shader();
    directionalShadowShader.createFromFiles(directionalShadowMapVShader, directionalShadowMapFShader);
    omniShadowShader.createFromFiles(omniShadowMapVShader, omniShadowMapGShader, omniShadowMapFShader);
}

void loadFile(){
    readOffFile(indicesOfBunny, verticesOfBunny, bunny);
    readOffFile(indicesOfBumpyCube, verticesOfBumpyCube, bumpyCube);
    readOffFile(indicesOfUnitCube, verticesOfUnitCube, unitCube);
    calculatePhongShadingNormals(indicesOfBunny, verticesOfBunny);
    calculatePhongShadingNormals(indicesOfBumpyCube, verticesOfBumpyCube);
    calculatePhongShadingNormals(indicesOfUnitCube, verticesOfUnitCube);
}

void renderObjects(){
    brickTexture.useTexture(GL_TEXTURE1);
    glUniform3f(uniformColor, 1.0f, 1.0f, 1.0f);
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    plane.renderPlane();
    brickTexture.disableTexture(GL_TEXTURE1);
    for(int i = 0; i < meshList.size(); ++i){
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(meshList[i]->getModel()));
        if(mouseClickMeshIndex == i){
            glUniform3f(uniformColor, 0.0f, 0.0f, 1.0f);
            meshList[i]->renderMeshWithPhongShading();
        }
        else {
            glUniform3f(uniformColor, 1.0f, 0.0f, 0.0f);
            meshList[i]->renderMeshWithPhongShading();
        }
    }
}

void renderDepthMapOfPointLight(){
    //render depth of scene for point light
    omniShadowShader.useShader();
    uniformModel = omniShadowShader.getModelLocation();
    uniformOmniLightPosition = omniShadowShader.getOmniLightPositionLocation();
    uniformFarPlane = omniShadowShader.getFarPlaneLocation();

    glUniform3f(uniformOmniLightPosition, pointLight.getPosition().x, pointLight.getPosition().y, pointLight.getPosition().z);
    glUniform1f(uniformFarPlane, pointLight.getFarPlane());
    omniShadowShader.setOmniLightMatrices(pointLight.calculateLightTransform());

    glViewport(0, 0, pointLight.getShadowMap()->getShadowWidth(), pointLight.getShadowMap()->getShadowHeight());
    pointLight.getShadowMap()->bindFramebuffer();
    glClear(GL_DEPTH_BUFFER_BIT);

    omniShadowShader.validate();
    renderObjects();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void renderDepthCubeOfDirectionalLight(){
    //render depth of scene for directional light
    directionalShadowShader.useShader();
    uniformModel = directionalShadowShader.getModelLocation();
    directionalShadowShader.setDirectionalLightTransform(directionalLight.calculateLightTransform());

    glViewport(0, 0, directionalLight.getShadowMap()->getShadowWidth(), directionalLight.getShadowMap()->getShadowHeight());
    directionalLight.getShadowMap()->bindFramebuffer();
    glClear(GL_DEPTH_BUFFER_BIT);

    directionalShadowShader.validate();
    renderObjects();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void renderScene(){
    glViewport(0, 0, bufferWidth, bufferHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderList[0].useShader();
    uniformModel = shaderList[0].getModelLocation();
    uniformProjection = shaderList[0].getProjectionLocation();
    uniformColor = shaderList[0].getColorLocation();
    uniformView = shaderList[0].getViewLocation();
    uniformCameraPosition = shaderList[0].getCameraPositionLocation();
    uniformSpecularIntensity = shaderList[0].getSpecularIntensityLocation();
    uniformShininess = shaderList[0].getShininessLocation();

    uniformPointLight.uniformAmbientIntensity = shaderList[0].getPointLightAmbientIntensityLocation();
    uniformPointLight.uniformDiffuseIntensity = shaderList[0].getPointLightDiffuseIntensityLocation();
    uniformPointLight.uniformLightColor = shaderList[0].getPointLightColorLocation();
    uniformPointLight.uniformLightPosition = shaderList[0].getPointLightPositionLocation();

    uniformDirectionalLight.uniformAmbientIntensity = shaderList[0].getDirectionalLightAmbientIntensityLocation();
    uniformDirectionalLight.uniformDiffuseIntensity = shaderList[0].getDirectionalLightDiffuseIntensityLocation();
    uniformDirectionalLight.uniformLightColor = shaderList[0].getDirectionalLightColorLocation();
    uniformDirectionalLight.uniformLightDirection = shaderList[0].getDirectionalLightDirectionLocation();

    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
    glUniform3f(uniformCameraPosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

    pointLight.useLight(uniformPointLight.uniformLightColor, uniformPointLight.uniformAmbientIntensity,
                        uniformPointLight.uniformDiffuseIntensity, uniformPointLight.uniformLightPosition);

    directionalLight.useLight(uniformDirectionalLight.uniformLightColor, uniformDirectionalLight.uniformAmbientIntensity,
                              uniformDirectionalLight.uniformDiffuseIntensity, uniformDirectionalLight.uniformLightDirection);

    material.useMaterial(uniformSpecularIntensity, uniformShininess);

    shaderList[0].setTexture(1);
    shaderList[0].setDirectionalShadowMap(2);
    shaderList[0].setOmniShadowMap(3);
    //set start from 1 to solve the struggling type on texture unit 0
    //at the very beginning all the texture will be bind to texture unit 0
    //sampler2D is different type of samplerCube

    shaderList[0].setDirectionalLightTransform(directionalLight.calculateLightTransform());
    directionalLight.getShadowMap()->useTexture(GL_TEXTURE2);

    shaderList[0].setFarPlane(pointLight.getFarPlane());
    pointLight.getShadowMap()->useTexture(GL_TEXTURE3);

    shaderList[0].validate();
    renderObjects();
}
