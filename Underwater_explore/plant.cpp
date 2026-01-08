#include "plant.h"

// LEARNOPENGL - didnt want to edit model.h so it works across devices - AI fix
// We cannot modify learnopengl's model.h, but it defines a non-inline
// TextureFromFile function, which causes multiple-definition linker errors
// when included from more than one .cpp file. To avoid this, we locally
// rename the function in this translation unit so the linker sees a
// different symbol name here than in other files (e.g. collectable.cpp).
#define TextureFromFile TextureFromFile_PlantTU
#include <learnopengl/model.h>
#undef TextureFromFile

Plant::Plant(vec3 position, int num) : centrePoint(position), size(num) {
    PlantModel = new Model("art/models/plant/plant.obj");
}

Plant::~Plant() {}

void Plant::draw(Shader& shaders, mat4 model, mat4 projection, mat4 view) {
    for (int i = 0; i < size; i++) {
        PlantModel->Draw(shaders);
        model = translate(model, vec3(0,2,0));
        shaders.setMat4("model", model);
    }
}