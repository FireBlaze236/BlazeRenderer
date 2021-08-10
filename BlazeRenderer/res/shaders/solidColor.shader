#shader vertex
#version 330

layout(location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos, 1.0);
}

#shader fragment
#version 330

out vec4 fragmentColor;

void main()
{
	fragmentColor = vec4(1.0, 0.5, 0.0, 1.0);
}