#pragma once

//framebuffer_size_callback() needs GlFW, so include moved here
#include <GLFW/glfw3.h>

//GLM
#include "glm/ext/vector_float3.hpp"

#include <cstdlib> // For srand() and rand()
#include <ctime> // For time()

class Player;
class Shader;

//Called on window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//Processes user input on a particular window
void ProcessUserInput(GLFWwindow* WindowIn, Player* player, Shader* shaders, Shader* terrainShaders);

//Called on mouse movement
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

//creates ImGui
ImGuiIO& init_ImGui_environment(GLFWwindow* window);