// ==================================================================
#version 330 core

// The final output color of each 'fragment' from our fragment shader.
out vec4 FragColor;

// Import our texture coordinates from vertex shader
in vec2 v_texCoord;

// If we have texture coordinates, they are stored in this sampler.
uniform sampler2D u_DiffuseMap; 

void main()
{
    vec3 diffuseColor;
	diffuseColor = texture(u_DiffuseMap, v_texCoord).rgb;
    FragColor = vec4(1.0, 0.83, 0.60, 1.0);
}
// ==================================================================