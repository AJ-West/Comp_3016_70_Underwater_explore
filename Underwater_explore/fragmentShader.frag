#version 460
//Colour value to send to next stage
out vec4 FragColor;

//Colour coordinates from last stage
//in vec3 colourFrag;

//Texture coordinates from last stage
in vec2 textureFrag;

uniform sampler2D texture_diffuse1;

void main()
{
    //Setting of colour coordinates to colour map
    //FragColor = vec4(colourFrag, 1.0f);

    //Setting of colour coordinates to colour map
    FragColor = texture(texture_diffuse1, textureFrag);
}