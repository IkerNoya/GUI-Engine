#version 460 core
layout (location = 0) in vec3 aPosition;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 transform;

out vec4 coords;

void main(){
	coords = transform * vec4(aPosition, 1.0);
	gl_Position = proj * view * transform * vec4(aPosition,1.0);
}