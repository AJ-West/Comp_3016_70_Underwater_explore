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

void Collectable::draw(Shader& shaders) {
    bottle->Draw(shaders);
    //glBindTexture(GL_TEXTURE_2D, Buffers[Textures]);
    //glBindVertexArray(VAOs[0]); //Bind buffer object to render
    //glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}