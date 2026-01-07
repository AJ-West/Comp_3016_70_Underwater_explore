#version 460

layout (location = 0) in vec3 position;

uniform mat4 mvpIn;
// need to change camMatrix to player matrix
uniform mat4 camMatrix;

void main()
{
	gl_Position = camMatrix * mvpIn * vec4(position, 1.0f);
}