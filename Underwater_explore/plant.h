#pragma once
#include <iostream>


#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "glm/ext/vector_float3.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

class Model;
class Shader;

using namespace std;
using namespace glm;

class Plant {
public:
    Plant(vec3 pos, int num);
    ~Plant();

    void draw(Shader& shaders, mat4 model, mat4 mvp, mat4 projection, mat4 view);

    vec3 getCentrePoint() { return centrePoint; }

private:
    int size;

    vec3 centrePoint;

    Model* PlantModel;

    //VAO vertex attribute positions in correspondence to vertex attribute type
    enum VAO_IDs { Triangles, Indices, Colours, Textures, NumVAOs = 2 };
    //VAOs
    GLuint VAOs[NumVAOs];

    //Buffer types
    enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };
    //Buffer objects
    GLuint Buffers[NumBuffers];
};