#version 460

layout (location = 0) in vec3 position;

uniform mat4 model;
// need to change camMatrix to player matrix
uniform mat4 camera;

void main()
{
	gl_Position = camera * model * vec4(position, 1.0f);
}