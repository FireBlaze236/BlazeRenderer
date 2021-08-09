#pragma once
#include "VertexArray.h"
#include "Shader.h"


class Renderer
{
private:
	
public:
	Renderer();
	~Renderer();
	void Clear();
	void ClearWithColor(float r, float g, float b, float a);
	void Draw(const VertexArray& va, const ElementBuffer& eb, const Shader& shader);
};

