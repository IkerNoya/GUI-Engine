#version 460 core
layout (location = 0) in vec3 aPointA;
layout (location = 1) in vec3 aPointB;
layout (location = 2) in vec3 color;

out vec3 outColor;

out VS_OUT {
	vec3 normal;
} vs_out;

uniform mat4 view;
uniform mat4 model;

void main(){
	
//	gl_Position = view * model * vec4(aPos,1.0);
}