#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "ElementBuffer.h"

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void AddElementBuffer(const ElementBuffer& eb);
};
