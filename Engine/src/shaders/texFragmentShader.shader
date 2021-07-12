#version 330 core
out vec4 fragColor;

in vec3 customColor;
in texCoord;
uniform sampler2D ourTexture;

void main()
{
	fragColor = texture(ourTexture, texCoord) * vec4(customColor, 1.0);
}