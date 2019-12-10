#include <iostream>

#include "Header.h"
#include "Editor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "PointLight.h"

using namespace std;

const GLint WIDTH = 1200;
const GLint HEIGHT = 800;
GLint bufferWidth = 0;
GLint bufferHeight = 0;


//Window mainWindow;
Camera camera;
PointLight pointLight;
Material material;

vector<Mesh*> meshList;
vector<Shader> shaderList;

vector<TriangleVertexIndex> indicesOfBunny;
vector<Vertex> verticesOfBunny;
vector<TriangleVertexIndex> indicesOfBumpyCube;
vector<Vertex> verticesOfBumpyCube;
vector<TriangleVertexIndex> indicesOfUnitCube;
vector<Vertex> verticesOfUnitCube;

glm::mat4 projection(1.0f);
glm::mat4 view(1.0f);
glm::mat4 model(1.0f);

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

bool keys[1024];

int mouseClickMeshIndex = -1;
bool isPerspective = false;

// Vertex Shader
static const char* vShader = "../Shader/vertexShader.txt";
//fragment shader
static const char* fShader = "../Shader/fragmentShader.txt";

string bumpyCube = "../meshFile/bumpy_cube.off";
string bunny = "../meshFile/bunny.off";
string unitCube = "../meshFile/unit_cube.off";

void framebufferSize(GLFWwindow* window, int width, int height);
void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
void handleMouseButton(GLFWwindow* window, int button, int action, int mods);
static void cursorPosition(GLFWwindow* window, double xpos, double ypos);

void createShaders();
void loadFile();
void changeToPerspective();
void changeToOrthographic();

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
    mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
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

    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f),
            0.872665f, 1.0f); // move 10 degree every time unit

    material = Material(1.0f, 132);
    pointLight = PointLight(1.0f, 1.0f, 1.0f,
                  0.1f, 0.6f,
                  -5.0f, 5.0f, 5.0f);

    GLuint uniformProjection = 0;
    GLuint uniformModel = 0;
    GLuint uniformColor = 0;
    GLuint uniformView = 0;
    GLuint uniformCameraPosition = 0;
    GLuint uniformSpecularIntensity = 0;
    GLuint uniformShininess = 0;
    GLuint uniformLightColor = 0;
    GLuint uniformLightPosition = 0;
    GLuint uniformAmbientIntensity = 0;
    GLuint uniformDiffuseIntensity = 0;
    GLuint uniformIsFlatShading = 0;
    GLuint uniformTriangleNormal = 0;

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

        view = camera.calculateViewMatrix();
        //update view

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glUseProgram(shader);
        shaderList[0].useShader();
        uniformModel = shaderList[0].getModelLocation();
        uniformProjection = shaderList[0].getProjectionLocation();
        uniformColor = shaderList[0].getColorLocation();
        uniformView = shaderList[0].getViewLocation();
        uniformCameraPosition = shaderList[0].getCameraPositionLocation();
        uniformAmbientIntensity = shaderList[0].getAmbientIntensityLocation();
        uniformDiffuseIntensity = shaderList[0].getDiffuseIntensityLocation();
        uniformLightColor = shaderList[0].getLightColorLocation();
        uniformLightPosition = shaderList[0].getLightPositionLocation();
        uniformSpecularIntensity = shaderList[0].getSpecularIntensityLocation();
        uniformShininess = shaderList[0].getShininessLocation();
        uniformIsFlatShading = shaderList[0].getIsFlatShadingLocation();
        uniformTriangleNormal = shaderList[0].getTriangleNormalLocation();

        pointLight.useLight(uniformLightColor, uniformAmbientIntensity,
                uniformDiffuseIntensity, uniformLightPosition);
        material.useMaterial(uniformSpecularIntensity, uniformShininess);

        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        glUniform3f(uniformCameraPosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);


        for(int i = 0; i < meshList.size(); ++i){
            if(mouseClickMeshIndex == i){
                glUniform3f(uniformColor, 0.0f, 0.0f, 1.0f);
                meshList[i]->renderMesh(uniformModel, uniformTriangleNormal, uniformIsFlatShading);
                //meshList[i]->renderMeshWithPhongShading(uniformModel, uniformIsFlatShading);
            }
            else {
                glUniform3f(uniformColor, 1.0f, 0.0f, 0.0f);
                meshList[i]->renderMesh(uniformModel, uniformTriangleNormal, uniformIsFlatShading);
            }
        }

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

void handleKeys(GLFWwindow* window, int key, int code, int action, int mode){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    switch (key){
        case GLFW_KEY_1:
            if(action == GLFW_PRESS){
                Mesh *mesh = new Mesh();
                mesh->createMesh(verticesOfUnitCube, indicesOfUnitCube, "UnitCube", 1);
                meshList.push_back(mesh);
            }
            break;
        case GLFW_KEY_2:
            if(action == GLFW_PRESS){
                Mesh *mesh = new Mesh();
                mesh->createMesh(verticesOfBumpyCube, indicesOfBumpyCube, "BumpyCube", 1);
                mesh->translation(-mesh->getBarycenter());
                mesh->scaling(0.1f, 0.1f, 0.1f);
                meshList.push_back(mesh);
            }
            break;
        case GLFW_KEY_3:
            if(action == GLFW_PRESS){
                Mesh *mesh = new Mesh();
                mesh->createMesh(verticesOfBunny, indicesOfBunny, "Bunny", 1);
                mesh->translation(-mesh->getBarycenter());
                mesh->scaling(4.0f, 4.0f, 4.0f);
                meshList.push_back(mesh);
            }
            break;

            //for camera control, sphere coordinate
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


            //change rendering way
        case GLFW_KEY_8:
            if(action == GLFW_PRESS){
                if(mouseClickMeshIndex != -1){
                    meshList[mouseClickMeshIndex]->updateRenderWay(1);
                }
            }
            break;
        case GLFW_KEY_9:
            if(action == GLFW_PRESS){
                if(mouseClickMeshIndex != -1){
                    meshList[mouseClickMeshIndex]->updateRenderWay(2);
                }
            }
            break;
        case GLFW_KEY_0:
            if(action == GLFW_PRESS){
                if(mouseClickMeshIndex != -1){
                    meshList[mouseClickMeshIndex]->updateRenderWay(3);
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
}

void loadFile(){
    readOffFile(indicesOfBunny, verticesOfBunny, bunny);
    readOffFile(indicesOfBumpyCube, verticesOfBumpyCube, bumpyCube);
    readOffFile(indicesOfUnitCube, verticesOfUnitCube, unitCube);
    calculatePhongShadingNormals(indicesOfBunny, verticesOfBunny);
    calculatePhongShadingNormals(indicesOfBumpyCube, verticesOfBumpyCube);
    calculatePhongShadingNormals(indicesOfUnitCube, verticesOfUnitCube);
}
