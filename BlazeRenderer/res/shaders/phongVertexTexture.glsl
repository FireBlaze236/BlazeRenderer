#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoords;

//Matrices
struct Transform {
	mat4 model;
	mat4 view;
	mat4 projection;
};

uniform Transform transform;



void main()
{
	gl_Position = transform.projection *  transform.view * transform.model * vec4(aPos, 1.0);
	fragPos = vec3(transform.model * vec4(aPos, 1.0));
	normal = mat3(transpose(inverse(transform.model))) * aNormal;
	texCoords = aTexCoords;
}