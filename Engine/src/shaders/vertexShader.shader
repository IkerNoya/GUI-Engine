#version 330 core
in vec4 pos;
in vec3 color;
in vec2 atexCoord;

out vec3 customColor;
out vec2 texCoord;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 proj;

void main() 
{
	customColor = color;
	gl_Position = proj * view * transform * pos;
	texCoord = atexCoord;
}