#pragma once

#include<iostream>
#include <vector>

#include <glad/glad.h> 

#include "FastNoiseLite.h"

#include "variables.h"

#include "stb_image.h"

using namespace std;

class Collectable;
class Plant;

class Flare {
public:
    Flare() {}
    ~Flare() {}

    void bind() {
        //Sets index of VAO
        glGenVertexArrays(NumVAOs, VAOs); //NumVAOs, VAOs
        //Binds VAO to a buffer
        glBindVertexArray(VAOs[0]); //VAOs[0]
        //Sets indexes of all required buffer objects
        glGenBuffers(NumBuffers, Buffers); //NumBuffers, Buffers
        //glGenBuffers(1, &EBO);

        //Binds vertex object to array buffer
        glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangles]);
        //Allocates buffer memory for the vertices of the 'Triangles' buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);

        //Binding & allocation for indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[Indices]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lightIndices), lightIndices, GL_STATIC_DRAW);

        //Allocates vertex attribute memory for vertex shader
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        //Index of vertex attribute for vertex shader
        glEnableVertexAttribArray(0);

        //Unbinding
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void draw() {
        glBindVertexArray(VAOs[0]); //Bind buffer object to render; VAOs[0]
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

private:
    unsigned int vertexBufferObject;

    //VAO vertex attribute positions in correspondence to vertex attribute type
    enum VAO_IDs { Triangles, Indices, Colours, Textures, NumVAOs = 2 };
    //VAOs
    GLuint VAOs[NumVAOs];

    //Buffer types
    enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };
    //Buffer objects
    GLuint Buffers[NumBuffers];

    GLfloat lightVertices[24] =
    { //     COORDINATES     //
        -0.1f, -0.1f,  0.1f,
        -0.1f, -0.1f, -0.1f,
         0.1f, -0.1f, -0.1f,
         0.1f, -0.1f,  0.1f,
        -0.1f,  0.1f,  0.1f,
        -0.1f,  0.1f, -0.1f,
         0.1f,  0.1f, -0.1f,
         0.1f,  0.1f,  0.1f
    };

    GLuint lightIndices[36] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7
    };
};