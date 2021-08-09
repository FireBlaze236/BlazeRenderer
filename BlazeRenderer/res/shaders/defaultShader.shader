#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;

struct Transform {
	mat4 model;
	mat4 view;
	mat4 projection;
};

out vec4 vertexColor;

uniform vec4 aColor;
uniform Transform transform;

void main()
{
	gl_Position = transform.projection *  transform.view * transform.model * vec4(aPos, 1.0);
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