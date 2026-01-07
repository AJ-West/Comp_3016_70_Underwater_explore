#version 460
//Colour value to send to next stage
out vec4 FragColor;

//Colour values from last stage
in vec3 colourFrag;
//Texture coordinates from last stage
in vec2 textureFrag;
//normals from last stage
in vec3 normalFrag;
//current position from last stage
in vec3 crntPosFrag;

//Gets texture from main function
uniform sampler2D texture_diffuse1;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;

void main()
{
    // ambient lighting
    float ambient = 0.20f;

    // diffuse lighting
	vec3 normal = normalize(normalFrag);
	vec3 lightDirection = normalize(lightPos - crntPosFrag);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

    // specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPosFrag);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

    //Setting of colour coordinates to colour map
    FragColor = texture(texture_diffuse1, textureFrag) * lightColor;// * (diffuse + ambient + specular);
}