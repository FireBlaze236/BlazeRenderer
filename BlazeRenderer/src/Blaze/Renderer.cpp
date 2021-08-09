#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Clear()
{
	GLCall(glClearColor(0.0, 0.0, 0.0, 0.0));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::ClearWithColor(float r, float g, float b, float a)
{
	GLCall(glClearColor(r, g, b, a));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const ElementBuffer& eb, const Shader& shader)
{
	shader.Bind();
	va.Bind();
	eb.Bind();
	
	GLCall(glDrawElements(GL_TRIANGLES, eb.GetCount(), GL_UNSIGNED_INT, nullptr));
}
