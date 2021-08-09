#pragma once
class ElementBuffer
{
private:
	unsigned int m_RendererID;
public:
	ElementBuffer(const unsigned int* data, unsigned int count);
	~ElementBuffer();

	void Bind() const;
	void UnBind() const;
};

