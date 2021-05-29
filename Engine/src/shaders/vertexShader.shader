#version 330 core
in vec4 pos;
in vec3 color;

out vec3 customColor;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 proj;

void main() 
{
	customColor = color;
	gl_Position = proj * view * transform * pos;
}