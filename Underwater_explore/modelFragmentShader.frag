#version 460
//Colour value to send to next stage
out vec4 FragColor;

//Texture coordinates from last stage
in vec2 textureFrag;
in vec3 lightCol;

uniform sampler2D texture_diffuse1;

void main()
{
    //Setting of colour coordinates to colour map
    vec4 colour = vec4(lightCol + vec3(0.25f,0.25f,0.25f), 0.05f);

    //Setting of colour coordinates to colour map
    FragColor = texture(texture_diffuse1, textureFrag)*colour;
}