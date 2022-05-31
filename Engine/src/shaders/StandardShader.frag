#version 460 core
out vec4 FragColor;

in vec3 position;
in vec3 color;
in vec3 normal;
in vec2 texCoord;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
struct Light {
	vec3 direction;
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;

uniform vec3 viewPos;

uniform float specularStrength = 0.5f;

uniform sampler2D ourTexture;

void main(){
	//ambient
	vec3 ambient =  light.ambient * vec3(texture(material.diffuse, texCoord));
	//diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
	//specular
	vec3 viewDir = normalize(viewPos - position);
	vec3 reflectDir = reflect(-lightDir, norm);
	// 32 representa como se esparce la iluminacion, 32 es el mas balanceado
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));

	vec3 result = (ambient + diffuse + specular) * color;
	FragColor = vec4(result, 1.0);
}