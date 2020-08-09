// ==================================================================
#version 330 core
// Read in our attributes stored from our vertex buffer object
// We explicitly state which is the vertex information
// (The first 3 floats are positional data, we are putting in our vector)
layout(location=0)in vec3 position; 
layout(location=1)in vec3 normals;
layout(location=2)in vec2 texCoord;

// If we are applying our camera, then we need to add some uniforms.
// Note that the syntax nicely matches glm's mat4!
uniform mat4 model; // Object space
uniform mat4 view; // Object space
uniform mat4 projection; // Object space

// If we have texture coordinates we can now use this as well
out vec2 v_texCoord;

void main()
{
	v_texCoord = texCoord;
	gl_Position = projection * view * model * vec4(position, 1.0f);
}
// ==================================================================