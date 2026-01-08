#pragma once

//framebuffer_size_callback() needs GlFW, so include moved here
#include <GLFW/glfw3.h>

//GLM
#include "glm/ext/vector_float3.hpp"

class Player;
class Shader;

//Called on window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//Processes user input on a particular window
void ProcessUserInput(GLFWwindow* WindowIn, Player* player);

//Called on mouse movement
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void SetMatrices(Shader& ShaderProgramIn, glm::mat4& Model);

//creates ImGui
ImGuiIO& init_ImGui_environment(GLFWwindow* window);