#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;


struct Transform {
	mat4 model;
	mat4 view;
	mat4 projection;
};

uniform Transform transform;

void main()
{
	gl_Position = transform.projection * transform.view * transform.model * vec4(aPos, 1.0);
}

#shader fragment
#version 330 core

out vec4 fragColor;

void main()
{
	fragColor = vec4(1.0);
}