#include "Renderer.h"

Renderer::Renderer()
{
	glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
}

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	//GLCall(glClearColor(0.0, 0.0, 0.0, 0.0));
}


void Renderer::ClearWithColor(float r, float g, float b, float a)
{
	
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	//GLCall(glClearColor(r, g, b, a));
}

void Renderer::Draw(const VertexArray& va, const ElementBuffer& eb, const Shader& shader)
{
	shader.Bind();
	va.Bind();
	eb.Bind();


	GLCall(glDrawElements(GL_TRIANGLES, eb.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const VertexArray& va, const Shader& shader, unsigned int count)
{
	shader.Bind();
	va.Bind();

	GLCall(glDrawArrays(GL_TRIANGLES, 0, count));

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


