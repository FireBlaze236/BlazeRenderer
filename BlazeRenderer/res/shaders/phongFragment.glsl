#version 330 core


in vec4 vertexColor;
in vec2 texCoords;
out vec4 FragColor;


uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, texCoords);
}