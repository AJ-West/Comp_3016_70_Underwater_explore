#version 460
//Triangle position with values retrieved from main.cpp
layout (location = 0) in vec3 position;
//Colour coordinates from last stage
//layout (location = 1) in vec3 colourVertex;
//Texture coordinates from last stage
layout (location = 2) in vec2 textureVertex;
// Normals
layout (location = 1) in vec3 normal;

//Model Matrix
uniform mat4 model;
//camera Matrix
uniform mat4 camera;
uniform mat4 mvpIn;

//Colour to send
//out vec3 colourFrag;

//Texture to send
out vec2 textureFrag;

//Normal to send
out vec3 normalFrag;

//position to send
out vec3 crntPosFrag;

void main()
{
    //Transformation applied to vertices
    crntPosFrag = vec3(model * vec4(position, 1.0));
    // Outputs the positions/coordinates of all vertices
	gl_Position = camera * vec4(crntPosFrag, 1.0);
    //Sending colour coordinates to next stage
    //colourFrag = colourVertex;
    //Sending texture coordinates to next stage
    textureFrag = textureVertex;
    //Sending normal to next stage
    normalFrag = normal;
}