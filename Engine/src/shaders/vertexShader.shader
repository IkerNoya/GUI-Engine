#version 330 core
in vec4 pos;
in vec3 color;

out vec3 customColor;

uniform mat4 transform;

void main() 
{
	customColor = color;
	gl_Position = transform * pos;
}