#version 460 core

layout(location=0) in vec3 inNormal;
layout(location=1) in vec3 inPosition; 
layout(location=2) in vec2 inTexCoord;

out vec3 normal;
out vec3 position;
out vec2 texCoord;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	normal = mat3(transpose(inverse(transform))) * inNormal;
	position = vec3(transform * vec4(inPosition, 1.0));
	texCoord = inTexCoord;

	gl_Position = proj * view * transform * vec4(inPosition, 1.0);
}