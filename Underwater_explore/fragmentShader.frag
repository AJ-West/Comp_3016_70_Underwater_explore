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
//texture opacity from last stage
in vec2 opacity;

//Gets texture from main function
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;

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

    // decreases light based off distance from light source
    float distance = length(lightPos - crntPosFrag);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.064 * distance * distance);
    //float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.016 * distance * distance);

    vec4 lighting = lightColor*attenuation;

    vec4 texture1 = texture(texture_diffuse1, textureFrag); // plains
    vec4 texture2 = texture(texture_diffuse2, textureFrag); // murky
    vec4 texture3 = texture(texture_diffuse3, textureFrag); // lava

    vec4 resultTexture = mix(texture1, texture2, opacity[0]);
    resultTexture = mix(resultTexture, texture3, opacity[1]);

    //Setting of colour coordinates to colour map
    FragColor = resultTexture * lighting * (diffuse + ambient + specular);
}