#pragma once
#include <string>
#include <unordered_map>

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_type;
	std::vector<unsigned int> slots;

public:
	Texture(const std::string& filepath);
	~Texture();

	void Bind();
	void Bind(unsigned int slot);
	void Unbind();
private:
	void LoadTexture(const std::string& file);
	
};

