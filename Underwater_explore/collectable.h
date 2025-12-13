#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

class Collectable {
public:
	Collectable();
	~Collectable();

	void bind();
    void draw();

private:

    float vertices[24] = {
        //positions             //colours
        0.0f, 0.0f, 0.0f,       1.0f, 1.0f, 0.0f, //top right
        0.5f, 0.0f, 0.0f,      1.0f, 1.0f, 0.0f, //bottom right
        0.25f, 0.0f, 0.5f,     1.0f, 1.0f, 0.0f, //bottom left
        0.25f, 0.5f, 0.25f,      1.0f, 1.0f, 0.0f //top left
    };

    unsigned int indices[12] = {
        0, 1, 3, //first triangle
        1, 2, 3, //second triangle
        0, 1, 3, //third triangle
        0, 2, 3 //fourth triangle
    };

    //VAO vertex attribute positions in correspondence to vertex attribute type
    enum VAO_IDs { Triangles, Indices, Colours, Textures, NumVAOs = 2 };
    //VAOs
    GLuint VAOs[NumVAOs];

    //Buffer types
    enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };
    //Buffer objects
    GLuint Buffers[NumBuffers];
};