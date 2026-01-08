#include "Player.h"

Player::Player(){
    soundEffects = createIrrKlangDevice();
    if (!soundEffects) {
        std::cerr << "Failed to load irrKlang DLL or initialize sound engine." << std::endl;
        return;
    }
    soundEffects->setSoundVolume(0.5f);
}

Player::~Player(){}

void Player::handleInput(GLFWwindow* WindowIn, Shader* shader, Shader* terrainShaders) {
    float movementSpeed = baseSpeed * deltaTime;
    if (glfwGetKey(WindowIn, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        movementSpeed *= 2;
    }

    //WASD controls
    if (glfwGetKey(WindowIn, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPosition += movementSpeed * cameraFront;
        updateFrag(shader, terrainShaders);
    }
    if (glfwGetKey(WindowIn, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPosition -= movementSpeed * cameraFront;
        updateFrag(shader, terrainShaders);
    }
    if (glfwGetKey(WindowIn, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPosition -= normalize(cross(cameraFront, cameraUp)) * movementSpeed;
        updateFrag(shader, terrainShaders);
    }
    if (glfwGetKey(WindowIn, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPosition += normalize(cross(cameraFront, cameraUp)) * movementSpeed;
        updateFrag(shader, terrainShaders);
    }
}

void Player::updateFrag(Shader* shader, Shader* terrainShaders) {
    shader->setVec3("lightPos", cameraPosition[0] + flareOffset[0], cameraPosition[1] + flareOffset[1], cameraPosition[2] + flareOffset[2]);
    //lightPositions[0] = cameraPos[0] + flareOffset[0];
    //lightPositions[1] = cameraPos[1] + flareOffset[1];
    //lightPositions[2] = cameraPos[2] + flareOffset[2];
    //glUniform3fv(glGetUniformLocation(Shaders.ID, "lightPositions"), lava.size() + 1, lightPositions.data());
    shader->setVec3("camPos", cameraPosition[0], cameraPosition[1], cameraPosition[2]);
    terrainShaders->use();
    terrainShaders->setVec3("lightPos", cameraPosition[0] + flareOffset[0], cameraPosition[1] + flareOffset[1], cameraPosition[2] + flareOffset[2]);
    terrainShaders->setVec3("camPos", cameraPosition[0], cameraPosition[1], cameraPosition[2]);
    shader->use();
}

bool Player::checkCollision(Collectable* collect) {
    vec3 tCentre = collect->getCentrePoint();
    float tSize = collect->getSize();

    vec3 diff = tCentre - cameraPosition;
    float mag = sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

    if (mag <= tSize) {
        soundEffects->play2D("Sound/pickup.mp3");
    }


    return mag <= tSize;
}