// ==================================================================
#version 330 core

// The final output color of each 'fragment' from our fragment shader.
out vec4 FragColor;

// Our light source data structure
struct PointLight{
    vec3 lightColor;
    vec3 lightPos;
    float ambientIntensity;

    float specularStrength;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float attentuateFactor;
};

uniform PointLight pointLights[2];

// Used for our specular highlights
uniform mat4 view;

// Take in our previous texture coordinates.
in vec3 FragPos;
in vec2 v_texCoord;
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

// If we have texture coordinates, they are stored in this sampler.
uniform sampler2D u_DiffuseMap; 
uniform sampler2D u_NormalMap; 

vec3 calcPointLight(vec3 norm, vec3 diffuseColor, PointLight pointLight);

void main()
{
	// Store the texture coordinates
	vec3 normal = texture(u_NormalMap, v_texCoord).rgb;        
	normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
	
    /*
    	vec3 color =  texture(u_DiffuseMap, v_texCoord).rgb;
	vec3 ambient = 0.1 * color;
    
    	vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
        float diff = max(dot(lightDir, normal), 0.0);
    	vec3 diffuse = diff * color;

    	vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
    	vec3 reflectDir = reflect(-lightDir, normal);
    	vec3 halfwayDir = normalize(lightDir + viewDir);
    	float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    	vec3 specular = vec3(0.2) * spec;
    
    	FragColor = vec4(ambient + diffuse + specular, 1.0);     
    */

    	// Store our final texture color
    	vec3 diffuseColor;
    	diffuseColor = texture(u_DiffuseMap, v_texCoord).rgb;

    	vec3 lightSum = vec3(0.0, 0.0, 0.0);
	for (int i = 0; i < 1; i++) {
    		lightSum += calcPointLight(normal, diffuseColor, pointLights[i]);
	}
    
    	// Final color + "how dark or light to make fragment"
    	FragColor = vec4(lightSum, 1.0);

}

vec3 calcPointLight(vec3 normal, vec3 diffuseColor, PointLight pointLight){

    	vec3 ambient = pointLight.ambientIntensity * pointLight.lightColor;

    	vec3 lightDir = normalize(pointLight.lightPos - FragPos);
    	//vec3 lightDir = normalize(TangentLightPos - TangentFragPos);        	
    	//float diffImpact = max(dot(norm, lightDir), 0.0);
	float diff = max(dot(lightDir, normal), 0.0);
	//vec3 diffuseLight = diffImpact * pointLight.lightColor;    
	vec3 diffuse = diff * diffuseColor;
            
    
    	//vec3 viewPos = vec3(0.0, 0.0, 0.0);
    	//vec3 viewDir = normalize(viewPos - FragPos);
	vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);  
    	vec3 specular = pointLight.specularStrength * spec * pointLight.lightColor;
	//vec3 specular = vec3(0.2) * spec;

    // Calculate Attenuation here
    // distance and lighting...
    float distance = length(pointLight.lightPos - FragPos);
    if(pointLight.attentuateFactor > 0.0) {
        float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));

        //diffuseLight *= attenuation;
	diffuse *= attenuation;
        ambient *= attenuation;
        specular *= attenuation;
    }
    // Our final color is now based on the texture.
    // That is set by the diffuseColor
    return diffuseColor * (diffuse + ambient + specular);
}


// ==================================================================
