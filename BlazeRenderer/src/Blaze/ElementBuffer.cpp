#include "ElementBuffer.h"
#include "Logger.h"
#include <glad/glad.h>

ElementBuffer::ElementBuffer(const unsigned int* data, unsigned int count)
	:m_RendererID(0), m_Count(0)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	Bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	
	m_Count = count;

	Unbind();
}

ElementBuffer::~ElementBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void ElementBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void ElementBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
