#include "Texture.h"
#include "Logger.h"
#include "glad/glad.h"
#include "stb_image/stb_image.h"

Texture::Texture(const std::string& filepath)
	: m_RendererID(0)
{
	LoadTexture(filepath);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}


void Texture::Bind(unsigned int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::LoadTexture(const std::string& file)
{
	GLCall(glGenTextures(1, &m_RendererID));

	//Texture parameters
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));


	Bind();

	stbi_set_flip_vertically_on_load(1);

	unsigned char* data;
	int width, height, nchannel;
	data = stbi_load("res/textures/container2.png", &width, &height, &nchannel, 4);

	if (!data)
	{
		LOG("Image loading error!");
		GLCall(glDeleteTextures(1, &m_RendererID));
		m_RendererID = 0;
	}
	else
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	}

	Unbind();
	stbi_image_free(data);
}
