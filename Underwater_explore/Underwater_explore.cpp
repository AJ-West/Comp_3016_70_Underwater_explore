// Underwater_explore.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//GLAD
#include <glad/glad.h>

//GLM
#include "glm/ext/vector_float3.hpp"
#include <glm/gtc/type_ptr.hpp> //Access to the value_ptr

//ASSIMP
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//LEARNOPENGL
#include <learnopengl/shader_m.h>
//#include <learnopengl/model.h>

#include "variables.h"

#include "Underwater_explore.h"

#include "proceduralGeneration.h"
#include "collectable.h"

#include "Player.h"
#include "plant.h"

using namespace glm;
using namespace std;

//Window
int windowWidth = 1280;
int windowHeight = 720;

GLuint program;

Player* player;

//Camera sideways rotation
float cameraYaw = -90.0f;
//Camera vertical rotation
float cameraPitch = 0.0f;
//if first time mouse is on window
bool mouseFirstEntry = true;
//Positions of camera from given last frame
float cameraLastXPos = 800.0f / 2.0f;
float cameraLastYPos = 600.0f / 2.0f;

//Transformations
mat4 transform;

//Time
//Last value of time change
float lastFrame = 0.0f;

//Model-View-Projection Matrix
mat4 mvp;
mat4 model;
mat4 view;
mat4 projection;

void SetMatrices(Shader& ShaderProgramIn, mat4& Model)
{
    mvp = projection * view * Model; //Setting of MVP
    ShaderProgramIn.setMat4("mvpIn", mvp); //Setting of uniform with Shader class
}

int main()
{
    //system("pause");
    //Initialisation of GLFW
    glfwInit();
    //Initialisation of 'GLFWwindow' object
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Underwater_explore", NULL, NULL);

    //Checks if window has been successfully instantiated
    if (window == NULL)
    {
        cout << "GLFW Window did not instantiate\n";
        glfwTerminate();
        return -1;
    }

    //Sets cursor to automatically bind to window & hides cursor pointer
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Binds OpenGL to window
    glfwMakeContextCurrent(window); 

    //Initialisation of GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "GLAD failed to initialise\n";
        return -1;
    }

    //Loading of shaders
    Shader Shaders("vertexShader.vert", "fragmentShader.frag");
    Shaders.use();
    Shader modelShaders("vertexShader.vert", "modelFragmentShader.frag");

    //Sets the viewport size within the window to match the window size of 1280x720
    glViewport(0, 0, 1280, 720);

    //Sets the framebuffer_size_callback() function as the callback for the window resizing event
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Sets the mouse_callback() function as the callback for the mouse movement event
    glfwSetCursorPosCallback(window, mouse_callback);

    // Create map
    ProcGen* map = new ProcGen();

    map->procTerrainGen();

    //get list of plants from the map
    vector<Plant*> plants = map->getPlants();

    //get collectables
    vector<Collectable*> collectables = map->generateCollectables();
    for (auto collect : collectables) {
        collect->bind();
    }

    //create player
    player = new Player();    

    //Determines if first entry of mouse into window
    bool mouseFirstEntry = true;
    
    //Terrain
    //Model matrix
    model = mat4(1.0f);
    //Scaling to zoom in
    model = scale(model, vec3(1.0f, 1.0f, 1.0f));
    //Rotation to look down
    model = rotate(model, radians(0.0f), vec3(1.0f, 0.0f, 0.0f));
    //Movement to position further back
    //model = translate(model, vec3(0.0f, -2.f, -1.5f));
    model = translate(model, vec3(0.0f, 0.0f, 0.0f));

    //Collectables
    mat4 CModel = mat4(1.0f);
    //Scaling to zoom in
    CModel = scale(CModel, vec3(0.1f, 0.1f, 0.1f));
    //Rotation to look down
    CModel = rotate(CModel, radians(0.0f), vec3(1.0f, 0.0f, 0.0f));
    //Movement to position further back
    //model = translate(model, vec3(0.0f, -2.f, -1.5f));
    CModel = translate(CModel, vec3(0.0f, 0.0f, 0.0f));

    //Plants
    mat4 PModel = mat4(1.0f);
    //Scaling to zoom in
    PModel = scale(PModel, vec3(0.1f, 0.1f, 0.1f));
    //Rotation to look down
    PModel = rotate(PModel, radians(0.0f), vec3(1.0f, 0.0f, 0.0f));
    //Movement to position further back
    //model = translate(model, vec3(0.0f, -2.f, -1.5f));
    PModel = translate(PModel, vec3(0.0f, 0.0f, 0.0f));

    //Projection matrix
    projection = perspective(radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
      
    //Game loop
    while (glfwWindowShouldClose(window) == false)
    {
        //Time
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //Input
        ProcessUserInput(window, player); //Takes user input

        //collision checks
        for (auto collect : collectables) {
            player->checkCollision(collect);
        }
        
        //Rendering
        glClearColor(0.25f, 0.0f, 1.0f, 1.0f); //Colour to display on cleared window
        glClear(GL_COLOR_BUFFER_BIT); //Clears the colour buffer
        glClear(GL_DEPTH_BUFFER_BIT); //Might need

        //glEnable(GL_CULL_FACE); //Discards all back-facing triangles
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        //Transformations & Drawing
        //Viewer orientation
        view = lookAt(player->getCameraPosition(), player->getCameraPosition() + player->getCameraFront(), player->getCameraUp()); //Sets the position of the viewer, the movement direction in relation to it & the world up direction
        SetMatrices(Shaders, model);

        //Drawing
        map->draw();
        // the collectables should be continuously rotating
        SetMatrices(Shaders, model);
        modelShaders.use();
        for (auto collect : collectables) {
            float time = (float)glfwGetTime();
            vec3 center = collect->getCentrePoint();
                        
            // adjust when and how to draw the model
            CModel = translate(CModel, center * 10.0f); // x10 due to model scale
            CModel = rotate(CModel, time * 0.5f, vec3(0.0f, 1.0f, 0.0f));
            CModel = translate(CModel, vec3(0.0f, sin(time), 0.0f));
            
            SetMatrices(Shaders, CModel);
            collect->draw(modelShaders);
            
            // return to origin with default values
            CModel = translate(CModel, vec3(0.0f, -sin(time), 0.0f));            
            CModel = rotate(CModel, -time * 0.5f, vec3(0.0f, 1.0f, 0.0f));
            CModel = translate(CModel, -center * 10.0f); // x10 due to model scale
        } 

        for (auto plant : plants) {
            float time = (float)glfwGetTime();
            vec3 center = plant->getCentrePoint();

            //Shift to location of plant
            PModel = translate(PModel, center*10.0f); // x10 to counteract scale of model

            SetMatrices(Shaders, PModel);
            plant->draw(modelShaders, PModel, mvp, projection, view);

            //return to origin
            PModel = translate(PModel, -center * 10.0f);
        }

        Shaders.use();
        //model = rotate(model, radians(0.0f), vec3(1.0f, 0.0f, 0.0f));
        SetMatrices(Shaders, model);
        //Refreshing
        glfwSwapBuffers(window); //Swaps the colour buffer
        glfwPollEvents(); //Queries all GLFW events
    }

    //Safely terminates GLFW
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //Resizes window based on contemporary width & height values
    glViewport(0, 0, width, height);
}

void ProcessUserInput(GLFWwindow* WindowIn, Player* player)
{
    //Closes window on 'exit' key press
    if (glfwGetKey(WindowIn, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(WindowIn, true);
    }

    player->handleInput(WindowIn);

    
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    //Initially no last positions, so sets last positions to current positions
    if (mouseFirstEntry)
    {
        cameraLastXPos = (float)xpos;
        cameraLastYPos = (float)ypos;
        mouseFirstEntry = false;
    }

    //Sets values for change in position since last frame to current frame
    float xOffset = (float)xpos - cameraLastXPos;
    float yOffset = cameraLastYPos - (float)ypos;

    //Sets last positions to current positions for next frame
    cameraLastXPos = (float)xpos;
    cameraLastYPos = (float)ypos;

    //Moderates the change in position based on sensitivity value
    const float sensitivity = 0.025f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    //Adjusts yaw & pitch values against changes in positions
    cameraYaw += xOffset;
    cameraPitch += yOffset;

    //Prevents turning up & down beyond 90 degrees to look backwards
    if (cameraPitch > 89.0f)
    {
        cameraPitch = 89.0f;
    }
    else if (cameraPitch < -89.0f)
    {
        cameraPitch = -89.0f;
    }

    //Modification of direction vector based on mouse turning
    vec3 direction;
    direction.x = cos(radians(cameraYaw)) * cos(radians(cameraPitch));
    direction.y = sin(radians(cameraPitch));
    direction.z = sin(radians(cameraYaw)) * cos(radians(cameraPitch));
    player->setCameraFront(normalize(direction));
}