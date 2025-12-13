#include "Player.h"

Player::Player(){}

Player::~Player(){}

void Player::handleInput(GLFWwindow* WindowIn) {
    float movementSpeed = baseSpeed * deltaTime;
    if (glfwGetKey(WindowIn, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        movementSpeed *= 2;
    }

    //WASD controls
    if (glfwGetKey(WindowIn, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPosition += movementSpeed * cameraFront;
    }
    if (glfwGetKey(WindowIn, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPosition -= movementSpeed * cameraFront;
    }
    if (glfwGetKey(WindowIn, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPosition -= normalize(cross(cameraFront, cameraUp)) * movementSpeed;
    }
    if (glfwGetKey(WindowIn, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPosition += normalize(cross(cameraFront, cameraUp)) * movementSpeed;
    }
}

void Player::checkCollision(Collectable* collect) {
    vec3 tCentre = collect->getCentrePoint();
    float tSize = collect->getSize();

    vec3 diff = tCentre - cameraPosition;
    float mag = sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

    if (mag <= tSize) {
        cout << "colliding" << '\n';
    }
}