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

void Renderer::SetDrawMode(DrawMode drawMode)
{
	switch (drawMode)
	{
	case DrawMode::FILL_TWO_SIDED:
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		break;
	case DrawMode::WIRE_TWO_SIDED:
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		break;
	case DrawMode::WIRE_FRONT:
		GLCall(glPolygonMode(GL_FRONT, GL_LINE));
		break;
	}
}


