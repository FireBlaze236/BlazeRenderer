#pragma once
class ElementBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	ElementBuffer(const unsigned int* data, unsigned int count);
	~ElementBuffer();

	void Bind() const;
	void Unbind() const;
	
	unsigned int GetCount() const { return m_Count; }
};

