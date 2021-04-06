#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Model.h"
#include "ModelInfo.h"
#include "Scenes.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "materials/ADSvalues.h"

using namespace std;

void processInput(GLFWwindow* window);
void mouseCallBack(GLFWwindow* window, double xpos, double ypos);
void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset);
void showDebugWindow();

//CONSTANTS
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;
const int  pointLightSourceCount = 4;

// camera settings
glm::vec3 cameraPos(0.0f, 0.0f, 6.0f);
Camera camera(cameraPos);
float cameraRoll = 0.0f;
float mouseLastX = SCR_WIDTH / 2.0;
float mouseLastY = SCR_HEIGHT / 2.0;
bool firstMouse = true;
bool locked = true;
float rollSensitivity = 0.1;

//frame timing
float deltaTime = 0.0f;

//DEBUG VARIABLES
    //lighting settings
    glm::vec3 pointLightColor(1.0f, 1.0f, 1.0f);
    glm::vec3 dirLightColor(1.0f, 1.0f, 1.0f);
    glm::vec3 bgColor(0.21, 0.21, 0.21);
    float constant = 1.0f;
    float linear = 0.07f;
    float quadratic = 0.04f;
    float pointLightDistance = 6.0f;
    float pointLightHeight = 0.0f;
    float pointLightAngle = 0.0f;
    int mode = 0;
    //object settings
    float tableWidth = 1.0;
    float tableLength = 1.0;
    float tableThickness = 0.122;
    float tableLegLength = 0.7;
    float restHeight = 1.0;
    float yaw = 0.0f;
    float pitch = 0.0f;
    float roll = 0.0f;
    //model settings
    bool useTexture_model = true;
    bool useTexture_scene = true;
    int currentModelIndex = 0;
    glm::vec3 modelTranslate(0.0f);
    glm::vec3 modelScale(0.02);
    Model* currentModel;
    Scenes::Scene currentScene;
    int currentSceneIndex = 0;

float camSpeed = 2.5f;
int materialIndex = 0;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Prakhar6969", glfwGetPrimaryMonitor() , NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    // glad: load all OpenGL function pointers
    // ---------------------------------------

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_DEPTH_TEST));

    cout << glGetString(GL_VERSION) << "\n";

    vector<float>wall[2];
    //back wall
    wall[0] = {
        -0.5,   0.0,    -0.5,    0.0,    0.0,    1.0,
        0.5,    0.0,    -0.5,    0.0,    0.0,    1.0,
        0.5,    1.0,    -0.5,    0.0,    0.0,    1.0,
        0.5,    1.0,    -0.5,    0.0,    0.0,    1.0,
        -0.5,   1.0,    -0.5,    0.0,    0.0,    1.0,
        -0.5,   0.0,    -0.5,    0.0,    0.0,    1.0,
        //right wall
        0.5,    0.0,    -0.5,    -1.0,    0.0,    0.0,
        0.5,    1.0,    -0.5,    -1.0,    0.0,    0.0,
        0.5,    1.0,     0.5,    -1.0,    0.0,    0.0,
        0.5,    1.0,     0.5,    -1.0,    0.0,    0.0,
        0.5,    0.0,     0.5,    -1.0,    0.0,    0.0,
        0.5,    0.0,    -0.5,    -1.0,    0.0,    0.0,
        //left wall
        -0.5,   0.0,    -0.5,    1.0,    0.0,    0.0,
        -0.5,   1.0,    -0.5,    1.0,    0.0,    0.0,
        -0.5,   1.0,     0.5,    1.0,    0.0,    0.0,
        -0.5,   1.0,     0.5,    1.0,    0.0,    0.0,
        -0.5,   0.0,     0.5,    1.0,    0.0,    0.0,
        -0.5,   0.0,    -0.5,    1.0,    0.0,    0.0
    };
    wall[1] = {
        -0.5,   1.0,   -0.5,    0.0,    -1.0,    0.0,
         0.5,   1.0,   -0.5,    0.0,    -1.0,    0.0,
         0.5,   1.0,    0.5,    0.0,    -1.0,    0.0,
         0.5,   1.0,    0.5,    0.0,    -1.0,    0.0,
        -0.5,   1.0,    0.5,    0.0,    -1.0,    0.0,
        -0.5,   1.0,   -0.5,    0.0,    -1.0,    0.0,
        //floor
        -0.5,   0.0,   -0.5,    0.0,    1.0,    0.0,
         0.5,   0.0,   -0.5,    0.0,    1.0,    0.0,
         0.5,   0.0,    0.5,    0.0,    1.0,    0.0,
         0.5,   0.0,    0.5,    0.0,    1.0,    0.0,
        -0.5,   0.0,    0.5,    0.0,    1.0,    0.0,
        -0.5,   0.0,   -0.5,    0.0,    1.0,    0.0
    };

    vector<float> cube_positions = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    vector<float>ames_window = {
        -1.0,-1.0,0.0,      0.0,0.0,1.0,
        -1.0,1.0,0.0,       0.0,0.0,1.0,
        2.0,3.0,0.0,        0.0,0.0,1.0,
        2.0,3.0,0.0,        0.0,0.0,1.0,
        2.0,-3.0,0.0,       0.0,0.0,1.0,
        -1.0,-1.0,0.0,      0.0,0.0,1.0
    };

    VertexArray* VAO_cube = new VertexArray();
    VertexBufferLayout* layout_cube = new VertexBufferLayout();
    layout_cube->push<float>(3);
    layout_cube->push<float>(3);
    VertexBuffer* VBO_cube = new VertexBuffer(cube_positions.data(), cube_positions.size() * sizeof(float));

    VAO_cube->addBuffer(*VBO_cube, *layout_cube);

    VertexArray* ames = new VertexArray();
    VertexBuffer* VBO_ames = new VertexBuffer(ames_window.data(), ames_window.size() * sizeof(float));
    ames->addBuffer(*VBO_ames, *layout_cube);

    glm::vec3 lightPos[pointLightSourceCount];

    glm::mat4 pointLightSource[pointLightSourceCount];

    Shader* shader_model = new Shader("res/shaders/basicModel.shader");
    shader_model->bind();
    for (int i = 0; i < pointLightSourceCount; i++)
        shader_model->setUniform3f("pointLights[" + to_string(i) + "].position", lightPos[i].x, lightPos[i].y, lightPos[i].z);
    shader_model->setUniform3f("dirLights[0].direction", 0, 0, -1);
    shader_model->unbind();

    Shader* shader_object = new Shader("res/shaders/phong.shader");
    shader_object->bind();
    shader_object->setUniform3f("dirLights[0].direction", 0, 0, -1);
    shader_object->unbind();

    Shader* shader_lightSource = new Shader("res/shaders/lightSource.shader");

    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 1920.0f / 1080.0f, 0.1f, 100.0f);
    glm::mat4 view = camera.getViewMatrix();

    //glm::mat4 mdl_wall = glm::mat4(1.0f); mdl_wall = glm::scale(mdl_wall, glm::vec3(7.0f, 5.0f, 7.0f));

    glm::mat4 tableTop = glm::mat4(1.0f); tableTop = glm::translate(tableTop, glm::vec3(0.0, tableLegLength, 0.0)); tableTop = glm::scale(tableTop, glm::vec3(tableLength, tableThickness, tableWidth));
    glm::mat4 tableLeg[4];
    tableLeg[0] = glm::mat4(1.0f); tableLeg[0] = glm::translate(tableLeg[0], glm::vec3(tableLength / 2 - tableThickness / 2, tableLegLength / 2, -(tableWidth / 2 - tableThickness / 2))); tableLeg[0] = glm::scale(tableLeg[0], glm::vec3(tableThickness, tableLegLength, tableThickness));
    tableLeg[1] = glm::mat4(1.0f); tableLeg[1] = glm::translate(tableLeg[1], glm::vec3(-(tableLength / 2 - tableThickness / 2), tableLegLength / 2, -(tableWidth / 2 - tableThickness / 2))); tableLeg[1] = glm::scale(tableLeg[1], glm::vec3(tableThickness, tableLegLength, tableThickness));
    tableLeg[2] = glm::mat4(1.0f); tableLeg[2] = glm::translate(tableLeg[2], glm::vec3(-(tableLength / 2 - tableThickness / 2), tableLegLength / 2, tableWidth / 2 - tableThickness / 2)); tableLeg[2] = glm::scale(tableLeg[2], glm::vec3(tableThickness, tableLegLength, tableThickness));
    tableLeg[3] = glm::mat4(1.0f); tableLeg[3] = glm::translate(tableLeg[3], glm::vec3(tableLength / 2 - tableThickness / 2, tableLegLength / 2, tableWidth / 2 - tableThickness / 2)); tableLeg[3] = glm::scale(tableLeg[3], glm::vec3(tableThickness, tableLegLength, tableThickness));
    glm::mat4 backRest = glm::mat4(1.0f); backRest = glm::translate(backRest, glm::vec3(tableLength / 2 - tableThickness / 2, tableLegLength + restHeight / 2, 0));; backRest = glm::scale(backRest, glm::vec3(tableThickness, restHeight, tableWidth));


    //Setup IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsClassic();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    

    Renderer renderer;
    Shader* curShader;
    currentScene = Scenes::sceneEnums[currentSceneIndex];
    Scenes::selectScene(currentScene);
    currentModel = new Model(ModelInfo::getPath(ModelInfo::modelEnums[currentModelIndex]));
    

    GLCall(glBindVertexArray(0));

    // render loop  
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        GLCall(glClearColor(bgColor.r, bgColor.g, bgColor.b, 1.0f));
        renderer.clear();

        camera.setSpeed(camSpeed);

        proj = glm::perspective(glm::radians(camera.getFOV()), 1920.0f / 1080.0f, 0.1f, 100.0f);
        view = camera.getViewMatrix();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        showDebugWindow();
        ImGui::Spacing();
        
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                
        lightPos[0] = glm::vec3(0, pointLightHeight, pointLightDistance / 2);
        lightPos[1] = glm::vec3(0, pointLightHeight, -pointLightDistance / 2);
        lightPos[2] = glm::vec3(pointLightDistance / 2, pointLightHeight, 0.0f);
        lightPos[3] = glm::vec3(-pointLightDistance / 2, pointLightHeight, 0.0f);
        glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(pointLightAngle), glm::vec3(0, 1, 0));
        for (int i = 0; i < pointLightSourceCount; i++)
        {
            pointLightSource[i] = rot;
            pointLightSource[i] = glm::translate(pointLightSource[i], lightPos[i]);
            pointLightSource[i] = glm::scale(pointLightSource[i], glm::vec3(0.5f));
            lightPos[i] = glm::vec3(rot * glm::vec4(lightPos[i], 1.0));
        }
        

        VAO_cube->bind();

        {
            shader_lightSource->bind();
            for (int i = 0; i < pointLightSourceCount; i++)
            {
                glm::mat4 MVP = proj * view * pointLightSource[i];
                shader_lightSource->setUniformMat4f("u_MVP", MVP);
                shader_lightSource->setUniform3f("lightColor", pointLightColor.r, pointLightColor.g, pointLightColor.b);
                GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
            }
        }

        shader_model->bind();
        shader_model->setUniformMat4f("proj", proj);
        shader_model->setUniformMat4f("view", view);
        shader_model->setUniform3f("viewPos", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
        for (int i = 0; i < pointLightSourceCount; i++)
            shader_model->setUniform3f("pointLights[" + to_string(i) + "].position", lightPos[i].x, lightPos[i].y, lightPos[i].z);
        for (int i = 0; i < pointLightSourceCount; i++)
        {
            shader_model->setUniform3f("pointLights[" + to_string(i) + "].ambient", pointLightColor.r, pointLightColor.g, pointLightColor.b);
            shader_model->setUniform3f("pointLights[" + to_string(i) + "].diffuse", pointLightColor.r, pointLightColor.g, pointLightColor.b);
            shader_model->setUniform3f("pointLights[" + to_string(i) + "].specular", pointLightColor.r, pointLightColor.g, pointLightColor.b);
        }
        shader_model->setUniform3f("dirLights[0].ambient", dirLightColor.r, dirLightColor.g, dirLightColor.b);
        shader_model->setUniform3f("dirLights[0].diffuse", dirLightColor.r, dirLightColor.g, dirLightColor.b);
        shader_model->setUniform3f("dirLights[0].specular", dirLightColor.r, dirLightColor.g, dirLightColor.b);

        shader_model->setUniform1f("a_constant", constant);
        shader_model->setUniform1f("a_linear", linear);
        shader_model->setUniform1f("a_quadratic", quadratic);

        shader_object->bind();
        shader_object->setUniformMat4f("proj", proj);
        shader_object->setUniformMat4f("view", view);
        shader_object->setUniform3f("viewPos", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
        for (int i = 0; i < pointLightSourceCount; i++)
            shader_object->setUniform3f("pointLights[" + to_string(i) + "].position", lightPos[i].x, lightPos[i].y, lightPos[i].z);
        for (int i = 0; i < pointLightSourceCount; i++)
        {
            shader_object->setUniform3f("pointLights[" + to_string(i) + "].ambient", pointLightColor.r, pointLightColor.g, pointLightColor.b);
            shader_object->setUniform3f("pointLights[" + to_string(i) + "].diffuse", pointLightColor.r, pointLightColor.g, pointLightColor.b);
            shader_object->setUniform3f("pointLights[" + to_string(i) + "].specular", pointLightColor.r, pointLightColor.g, pointLightColor.b);
        }
        shader_object->setUniform3f("dirLights[0].ambient", dirLightColor.r, dirLightColor.g, dirLightColor.b);
        shader_object->setUniform3f("dirLights[0].diffuse", dirLightColor.r, dirLightColor.g, dirLightColor.b);
        shader_object->setUniform3f("dirLights[0].specular", dirLightColor.r, dirLightColor.g, dirLightColor.b);

        shader_object->setUniform1f("a_constant", constant);
        shader_object->setUniform1f("a_linear", linear);
        shader_object->setUniform1f("a_quadratic", quadratic);

        //ADD DIFFERENT MATERIALS HERE
        shader_object->setUniform3f("material.ambient", Materials::ambient[materialIndex][0], Materials::ambient[materialIndex][1], Materials::ambient[materialIndex][2]);
        shader_object->setUniform3f("material.diffuse", Materials::diffuse[materialIndex][0], Materials::diffuse[materialIndex][1], Materials::diffuse[materialIndex][2]);
        shader_object->setUniform3f("material.specular", Materials::specular[materialIndex][0], Materials::specular[materialIndex][1], Materials::specular[materialIndex][2]);
        shader_object->setUniform1f("material.shininess", Materials::shinness[materialIndex]);
        
        if (mode == 1 && useTexture_model)
        {
            shader_model->bind();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), modelTranslate);
            model = glm::scale(model, modelScale);
            shader_model->setUniformMat4f("model", model);
            currentModel->Draw(shader_model, "material.");
        }
        
        if ((mode == 0) || (mode == 1 && !useTexture_model))
        {
            shader_object->bind();

            if (mode == 0) {
                tableTop = glm::mat4(1.0f); tableTop = glm::translate(tableTop, glm::vec3(0.0, tableLegLength, 0.0)); tableTop = glm::scale(tableTop, glm::vec3(tableLength, tableThickness, tableWidth));
                tableLeg[0] = glm::mat4(1.0f); tableLeg[0] = glm::translate(tableLeg[0], glm::vec3(tableLength / 2 - tableThickness / 2, tableLegLength / 2, -(tableWidth / 2 - tableThickness / 2))); tableLeg[0] = glm::scale(tableLeg[0], glm::vec3(tableThickness, tableLegLength, tableThickness));
                tableLeg[1] = glm::mat4(1.0f); tableLeg[1] = glm::translate(tableLeg[1], glm::vec3(-(tableLength / 2 - tableThickness / 2), tableLegLength / 2, -(tableWidth / 2 - tableThickness / 2))); tableLeg[1] = glm::scale(tableLeg[1], glm::vec3(tableThickness, tableLegLength, tableThickness));
                tableLeg[2] = glm::mat4(1.0f); tableLeg[2] = glm::translate(tableLeg[2], glm::vec3(-(tableLength / 2 - tableThickness / 2), tableLegLength / 2, tableWidth / 2 - tableThickness / 2)); tableLeg[2] = glm::scale(tableLeg[2], glm::vec3(tableThickness, tableLegLength, tableThickness));
                tableLeg[3] = glm::mat4(1.0f); tableLeg[3] = glm::translate(tableLeg[3], glm::vec3(tableLength / 2 - tableThickness / 2, tableLegLength / 2, tableWidth / 2 - tableThickness / 2)); tableLeg[3] = glm::scale(tableLeg[3], glm::vec3(tableThickness, tableLegLength, tableThickness));
                backRest = glm::mat4(1.0f); backRest = glm::translate(backRest, glm::vec3(tableLength / 2 - tableThickness / 2, tableLegLength + restHeight / 2, 0));; backRest = glm::scale(backRest, glm::vec3(tableThickness, restHeight, tableWidth));

                {
                    VAO_cube->bind();
                    shader_object->setUniformMat4f("model", tableTop);
                    GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
                    shader_object->setUniformMat4f("model", tableLeg[0]);
                    GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
                    shader_object->setUniformMat4f("model", tableLeg[1]);
                    GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
                    shader_object->setUniformMat4f("model", tableLeg[2]);
                    GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
                    shader_object->setUniformMat4f("model", tableLeg[3]);
                    GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
                    shader_object->setUniformMat4f("model", backRest);
                    GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
                }
            }
            else {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), modelTranslate);
                model = glm::scale(model, modelScale);
                shader_object->setUniformMat4f("model", model);
                currentModel->Draw(shader_object, "material.");
            }
        }

        if (mode == 2)
        {
            if (useTexture_scene)
                Scenes::drawScene(currentScene, shader_object, shader_model);
            else Scenes::drawScene(currentScene, shader_object, shader_object);
        }

        if (mode == 3)
        {
            shader_object->bind();
            VAO_cube->bind();

            glm::quat q(glm::vec3(glm::radians(pitch), glm::radians(yaw), glm::radians(roll)));
            glm::mat4 rot = glm::toMat4(q);
            glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(5, 0.1, 0.1));
            shader_object->setUniformMat4f("model", rot*scale );
            shader_object->setUniform3f("material.ambient", 0.0, 0.0, 0.0);
            shader_object->setUniform3f("material.diffuse", 1.0, 0.0, 0.0);
            shader_object->setUniform3f("material.specular", 0.3, 0.3, 0.3);
            shader_object->setUniform1f("material.shininess", 0.1 * 128);
            GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
            scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 5, 0.1));
            shader_object->setUniformMat4f("model", rot* scale);
            shader_object->setUniform3f("material.ambient", 0.0, 0.0, 0.0);
            shader_object->setUniform3f("material.diffuse", 0.0, 1.0, 0.0);
            shader_object->setUniform3f("material.specular", 0.3, 0.3, 0.3);
            shader_object->setUniform1f("material.shininess", 0.1 * 128);
            GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
            scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.1, 5));
            shader_object->setUniformMat4f("model", rot * scale);
            shader_object->setUniform3f("material.ambient", 0.0, 0.0, 0.0);
            shader_object->setUniform3f("material.diffuse", 0.0, 0.0, 1.0);
            shader_object->setUniform3f("material.specular", 0.3, 0.3, 0.3);
            shader_object->setUniform1f("material.shininess", 0.1 * 128);
            GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
        }

        if (mode == 4)
        {
            shader_object->bind();
            ames->bind();

            glm::mat4 model(1.0f);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            shader_object->setUniformMat4f("model", model);
            GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
        }
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Shutdown IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}

/*
    This is a event handler for keyboard inputs.
    [WASD] is for camera movements.
    Press M to LOCK/FREE mouse.
    If mouse is in a locked state, the cursur becomes visible and only [WASD] is recorded. Changes in YAW and PITCH are ignored.
    Pressing Esc terminates the application.
*/
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // set camera speed acc to frame refresh rate
    deltaTime = glfwGetTime() - deltaTime;
    float currentTime = glfwGetTime();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboardInput(camera_movements::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboardInput(camera_movements::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboardInput(camera_movements::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboardInput(camera_movements::RIGHT, deltaTime);
    deltaTime = currentTime;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        if (locked)
        {
            firstMouse = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(window, mouseCallBack); // for mouse movements
            glfwSetScrollCallback(window, scrollCallBack); // for mouse scrolls
            locked = false;
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPosCallback(window, NULL); // for mouse movements
            glfwSetScrollCallback(window, NULL); // for mouse scrolls   
            locked = true;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        camera.processCameraRoll(-rollSensitivity);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        camera.processCameraRoll(rollSensitivity);
    }

}

/*
    This function handles changes in YAW and PITCH of the camera.
    This function records the changes in the cursor position.
    Moving mouse in the forward/backward direction changes the PITCH.
    Moving mouse in the  left/right direction changes the YAW.
*/
void mouseCallBack(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        mouseLastX = xpos;
        mouseLastY = ypos;
        firstMouse = false;
    }

    float x_offset = -xpos + mouseLastX;
    float y_offset = mouseLastY - ypos;
    mouseLastX = xpos;
    mouseLastY = ypos;
    camera.processMouseMovement(x_offset, y_offset);
}

/*
    This function handles the ZOOM feature by keeping track of the scroll wheel movememnts.
    Scrolling Up ZOOMS IN which is equivalent to DECREASING the FOV.
    Scrolling Down ZOOMS OUT which is equivalent to INCREASING the FOV.
*/
void scrollCallBack(GLFWwindow* window, double x_offset, double y_offset)
{
    camera.processMouseScroll(y_offset);
}

/*
    Displays the ImGUI Debug Window.
    The user can change some basic parameters of the application to see difference results.
*/
void showDebugWindow()
{
    ImGui::Text("prakhar says hello. #6969");
    ImGui::Spacing();
    if (ImGui::CollapsingHeader("Help"))
    {
        ImGui::Text("Still Under Construction :/");
    }
    ImGui::Spacing();
    if (ImGui::CollapsingHeader("Configurations"))
    {
        if (ImGui::TreeNode("General"))
        {
            ImGui::ColorEdit3("Background Color", glm::value_ptr(bgColor));
            ImGui::ShowStyleSelector("Theme");
            ImGui::Combo("Choose Material", &materialIndex, Materials::names, Materials::count);
            ImGui::SliderFloat("Camera Speed", &camSpeed, 0, 10);
            ImGui::NewLine();
            ImGui::SameLine(200);
            if (ImGui::Button("Recenter Camera"))
                camera.recenter(cameraPos);

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Lighting"))
        {
            ImGui::ColorEdit3("Dir Source Color", glm::value_ptr(dirLightColor));
            ImGui::Spacing();
            ImGui::ColorEdit3("Point Source Color", glm::value_ptr(pointLightColor));
            ImGui::Text("Attenuation Factor");
            ImGui::SliderFloat("Constant", &constant,  0.1, 5);
            ImGui::SliderFloat("Linear", &linear, 0, 1);
            ImGui::SliderFloat("Quadratic", &quadratic, 0, 1, "%.4f");
            ImGui::Text("Location");
            ImGui::DragFloat("Height", &pointLightHeight, 0.1, -5.0, 50.0);
            ImGui::DragFloat("Distace", &pointLightDistance, 0.1, 1.0, 50.0);
            ImGui::DragFloat("Angle", &pointLightAngle, 0.1, 0.0f, 90.0f);
            ImGui::TreePop();
        }
    }
    ImGui::Spacing();
    ImGui::Text("Render Mode");
    ImGui::RadioButton("Object", &mode, 0); ImGui::SameLine();
    ImGui::RadioButton("Model", &mode, 1); ImGui::SameLine();
    ImGui::RadioButton("Scene", &mode, 2); ImGui::SameLine();
    ImGui::RadioButton("Rotations", &mode, 3); ImGui::SameLine();
    ImGui::RadioButton("Ames Window", &mode, 4);
    //ImGui::RadioButton("Scene Creator", &mode, 3);
    ImGui::Spacing();
    ImGui::Spacing();
    if (ImGui::CollapsingHeader("Object Settings"))
    {
        ImGui::SliderFloat("Table Width", &tableWidth, 0, 5); 
        ImGui::SliderFloat("Table Length", &tableLength, 0, 5); 
        ImGui::SliderFloat("Table Thickness", &tableThickness, 0, 5); 
        ImGui::SliderFloat("Table Leg Length", &tableLegLength, 0, 5); 
        ImGui::SliderFloat("Backrest height", &restHeight, 0, 5);
    }
    ImGui::Spacing();
    ImGui::Spacing();
    if (ImGui::CollapsingHeader("Model Settings"))
    {
        ImGui::Checkbox("Use textures##model", &useTexture_model);
        ImGui::Spacing();
        ImGui::Text("Scaling");
        ImGui::DragFloat("X##1", &modelScale.x, 0.01, -2, 2);
        ImGui::DragFloat("Y##1", &modelScale.y, 0.01, -2, 2);
        ImGui::DragFloat("Z##1", &modelScale.z, 0.01, -2, 2);
        ImGui::Spacing();
        ImGui::Text("Translation");
        ImGui::DragFloat("X##2", &modelTranslate.x, 0.01, -10, 10);
        ImGui::DragFloat("Y##2", &modelTranslate.y, 0.01, -10, 10);
        ImGui::DragFloat("Z##2", &modelTranslate.z, 0.01, -10, 10);
        ImGui::Spacing();
        ImGui::Combo("Choose Model", &currentModelIndex, ModelInfo::modelNames, ModelInfo::count);
        ImGui::NewLine();
        ImGui::SameLine(200);
        if (ImGui::Button("Change Model"))
        {
            currentModel = new Model(ModelInfo::getPath(ModelInfo::modelEnums[currentModelIndex]));
            GLCall(glBindTexture(GL_TEXTURE_2D, 0));
        }
    }
    ImGui::Spacing();
    ImGui::Spacing();
    if (ImGui::CollapsingHeader("Scene Settings"))
    {
        ImGui::Checkbox("Use textures##scene", &useTexture_scene);
        ImGui::Spacing();
        ImGui::Combo("Chose Scene", &currentSceneIndex, Scenes::sceneNames, Scenes::count);
        ImGui::NewLine();
        ImGui::SameLine(200);
        if (ImGui::Button("Change Scene"))
        {
            currentScene = Scenes::sceneEnums[currentSceneIndex];
            Scenes::selectScene(currentScene);
            GLCall(glBindTexture(GL_TEXTURE_2D, 0));
        }
    }
    ImGui::Spacing();
    ImGui::Spacing();
    if (ImGui::CollapsingHeader("Euler Angles"))
    {
        ImGui::DragFloat("PITCH", &pitch,0.1, -90, 90);
        ImGui::DragFloat("YAW", &yaw,0.1, -180, 180);
        ImGui::DragFloat("ROLL", &roll,0.1, -180, 180);
    }
}