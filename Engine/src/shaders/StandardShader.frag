#version 460 core
out vec4 FragColor;

in vec3 position;
in vec3 color;
in vec3 normal;
in vec2 texCoord;

uniform vec3 lightColor = vec3(1.0);
uniform vec3 objectColor = vec3(1.0f);

uniform sampler2D ourTexture;

void main(){
	float ambientStrength = 0.5;
	vec3 ambient = ambientStrength * lightColor;
	vec3 result = ambient * objectColor;
	FragColor = vec4(result, 1.0) * texture(ourTexture, texCoord) * vec4(color, 1.0);
}