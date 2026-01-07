#version 460
//Colour value to send to next stage
out vec4 FragColor;

//Colour values from last stage
//in vec3 colourFrag;
//Texture coordinates from last stage
in vec2 textureFrag;
//normals from last stage
in vec3 normalFrag;
//current position from last stage
in vec3 crntPosFrag;

//Gets texture from main function
uniform sampler2D texture_diffuse1;

//get number of lights
uniform float lightNum;
// get list of all light colours (size of maximum number of light sources)
uniform vec4 lightColors[500];
// get list of all light positions
uniform vec3 lightPositions[500];
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
	vec3 lightDirection = normalize(lightPositions[0] - crntPosFrag);
	vec3 viewDirection = normalize(camPos - crntPosFrag);
    vec3 halfwayDirection = normalize(lightDirection + viewDirection);
	float diffuse = max(dot(normal, halfwayDirection), 0.0f);
    
    // specular lighting
	float specularLight = 0.50f;
	vec3 reflectionDirection = reflect(-halfwayDirection, normal);
	float specAmount = pow(max(dot(normal, halfwayDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

    // decreases light based off distance from light source
    float distance = length(lightPositions[0] - crntPosFrag);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.064 * distance * distance);

    vec4 lighting = lightColors[0] * attenuation;

    for(int i = 1; i<lightNum; i++){
        // diffuse lighting
	    normal = normalize(normalFrag);
        lightDirection = normalize(lightPositions[i] - crntPosFrag);
        halfwayDirection = normalize(lightDirection + viewDirection);
	    diffuse += max(dot(normal, halfwayDirection), 0.0f);

        // specular lighting
	    viewDirection = normalize(camPos - crntPosFrag);
	    specAmount = pow(max(dot(normal, halfwayDirection), 0.0f), 8);
	    specular += specAmount * specularLight;

        // decreases light based off distance from light source
        distance = length(lightPositions[i] - crntPosFrag);
        attenuation = 1.0 / (1.0 + 0.09 * distance + 0.064 * distance * distance);

        lighting += lightColors[i]*attenuation;
    }

    // ambient lighting
    /*float ambient = 0.20f;

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

    // decreases light based off distance from light source
    float distance = length(lightPos - crntPosFrag);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.064 * distance * distance);

    vec4 lighting = lightColor*attenuation;*/

    //Setting of colour coordinates to colour map
    FragColor = texture(texture_diffuse1, textureFrag) * lighting * (diffuse + ambient + specular);
}
/*
#version 460
//Colour value to send to next stage
out vec4 FragColor;

//Texture coordinates from last stage
in vec2 textureFrag;
// Gets the color of the light from the main function
uniform vec4 lightColor;

uniform sampler2D texture_diffuse1;

void main()
{
    //Setting of colour coordinates to colour map
    //vec4 colour = vec4(lightColor,0.05f);// + vec3(0.25f,0.25f,0.25f), 0.05f);

    //Setting of colour coordinates to colour map
    FragColor = texture(texture_diffuse1, textureFrag)*lightColor;
}*/