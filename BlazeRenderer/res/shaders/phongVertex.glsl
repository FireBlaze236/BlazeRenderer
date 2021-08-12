#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;

struct Transform {
	mat4 model;
	mat4 view;
	mat4 projection;
};

out vec4 vertexColor;
out vec2 texCoords;

uniform vec4 aColor;
uniform Transform transform;

void main()
{
	gl_Position = transform.projection *  transform.view * transform.model * vec4(aPos, 1.0);
	vertexColor = aColor;
	texCoords = aTexCoords;
}