#pragma once

//GLFW
#include <GLFW/glfw3.h>
#include "glm/ext/vector_float3.hpp"
#include <glm/gtc/type_ptr.hpp> 

#include "variables.h"

using namespace glm;
using namespace std;

class Player {
public:
	Player();
	~Player();

	void handleInput(GLFWwindow* WindowIn);

	//getters
	vec3 getCameraPosition() { return cameraPosition; }
	vec3 getCameraFront() { return cameraFront; }
	vec3 getCameraUp() { return cameraUp; }

	//setters
	void setCameraFront(vec3 newFront) { cameraFront = newFront; }

private:
	float baseSpeed = 2.0f;

	//Relative position within world space
	vec3 cameraPosition = vec3(-24.5f, 5.0f, -24.5f);
	//The direction of travel
	vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
	//Up position within world space
	vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

};
