#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;

out vec4 vertexColor;

uniform vec4 aColor;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	vertexColor = aColor;
}

#shader fragment
#version 330 core

in vec4 vertexColor;
out vec4 FragColor;

void main()
{
	FragColor = vertexColor;
}