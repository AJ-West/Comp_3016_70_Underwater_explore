#include "collectable.h"
//LEARNOPENGL
#include <learnopengl/model.h>

Collectable::Collectable(vec3 position): centrePoint(position){
    vertices[0] = centrePoint.x + 0.0f;
    vertices[1] = centrePoint.y + 0.0f;
    vertices[2] = centrePoint.z + 0.0f;

    vertices[8] = centrePoint.x + size;
    vertices[9] = centrePoint.y + 0.0f;
    vertices[10] = centrePoint.z + 0.0f;

    vertices[16] = centrePoint.x + size;
    vertices[17] = centrePoint.y + size;
    vertices[18] = centrePoint.z + size;

    vertices[24] = centrePoint.x + 0.0f;
    vertices[25] = centrePoint.y + 0.0f;
    vertices[26] = centrePoint.z + size;

    bottle = new Model("art/models/bottle/bottle.obj");
}

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Colours
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Textures
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //Textures to generate
    glGenTextures(NumBuffers, Buffers);

    //Unbinding
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //Binding texture to type 2D texture
    glBindTexture(GL_TEXTURE_2D, Buffers[Textures]);

    //Selects x axis (S) of texture bound to GL_TEXTURE_2D & sets to repeat beyond normalised coordinates
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //Selects y axis (T) equivalently
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Sets to use linear interpolation between adjacent mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //Sets to use linear interpolation upscaling (past largest mipmap texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Parameters that will be sent & set based on retrieved texture
    int width, height, colourChannels;
    //Retrieves texture data
    unsigned char* data = stbi_load("art/rubbish.png", &width, &height, &colourChannels, 0);

    if (data) //If retrieval successful
    {
        GLenum format = (colourChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        //Generation of texture from retrieved texture data
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //Automatically generates all required mipmaps on bound texture
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else //If retrieval unsuccessful
    {
        cout << "Failed to load texture.\n";
        return;
    }

    //Clears retrieved texture from memory
    stbi_image_free(data);

}

void Collectable::draw(Shader& shaders) {
    bottle->Draw(shaders);
    //glBindTexture(GL_TEXTURE_2D, Buffers[Textures]);
    //glBindVertexArray(VAOs[0]); //Bind buffer object to render
    //glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}