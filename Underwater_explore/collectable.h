#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "glm/ext/vector_float3.hpp"

using namespace glm;

class Collectable {
public:
	Collectable();
	~Collectable();

	void bind();
    void draw();

    //getters
    vec3 getCentrePoint() { return centerPoint; }
    float getSize() { return size; }

private:
    float size = 0.25f;

    float vertices[24] = {
        //positions             //colours
        0.0f, 0.0f, 0.0f,       1.0f, 1.0f, 0.0f, //top right
        size*2, 0.0f, 0.0f,      1.0f, 1.0f, 0.0f, //bottom right
        size, 0.0f, size * 2,     1.0f, 1.0f, 0.0f, //bottom left
        size, size * 2, size,      1.0f, 1.0f, 0.0f //top left
    };

    unsigned int indices[12] = {
        0, 1, 3, //first triangle
        1, 2, 3, //second triangle
        0, 1, 3, //third triangle
        0, 2, 3 //fourth triangle
    };

    vec3 centerPoint = vec3(size, size, size);

    //VAO vertex attribute positions in correspondence to vertex attribute type
    enum VAO_IDs { Triangles, Indices, Colours, Textures, NumVAOs = 2 };
    //VAOs
    GLuint VAOs[NumVAOs];

    //Buffer types
    enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };
    //Buffer objects
    GLuint Buffers[NumBuffers];
};