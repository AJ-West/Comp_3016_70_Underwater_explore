#include "collectable.h"

Collectable::Collectable(){}

Collectable::~Collectable(){}

void Collectable::bind() {
    //Sets index of VAO
    glGenVertexArrays(NumVAOs, VAOs); //NumVAOs, VAOs
    //Binds VAO to a buffer
    glBindVertexArray(VAOs[0]); //VAOs[0]
    //Sets indexes of all required buffer objects
    glGenBuffers(NumBuffers, Buffers); //NumBuffers, Buffers
    //glGenBuffers(1, &EBO);

    //Binds vertex object to array buffer
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangles]); //Buffers[Triangles]
    //Allocates buffer memory for the vertices of the 'Triangles' buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Binding & allocation for indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[Indices]); //Buffers[Indices]
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Allocation & indexing of vertex attribute memory for vertex shader
    //Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Colours
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Unbinding
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Collectable::draw() {
    glBindTexture(GL_TEXTURE_2D, Buffers[Textures]);
    glBindVertexArray(VAOs[0]); //Bind buffer object to render
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}