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
    FragColor = texture(u_DiffuseMap, v_texCoord) * vec4(0.55, 0.1, 0.0, 1.0);
}
// ==================================================================