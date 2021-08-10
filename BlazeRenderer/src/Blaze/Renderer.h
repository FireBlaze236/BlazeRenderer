#pragma once
#include "VertexArray.h"
#include "Shader.h"

enum class DrawMode {
	FILL_TWO_SIDED, WIRE_TWO_SIDED, WIRE_FRONT
};

class Renderer
{
private:
	
public:
	Renderer();
	~Renderer();
	void Clear();

	void ClearWithColor(float r, float g, float b, float a);
	void Draw(const VertexArray& va, const ElementBuffer& eb, const Shader& shader);

	void Draw(const VertexArray& va, const Shader& shader, unsigned int count);

	void SetDrawMode(DrawMode drawMode);
};

