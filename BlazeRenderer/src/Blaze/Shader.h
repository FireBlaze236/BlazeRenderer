#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_Filepath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, unsigned int> m_UniformMap;

public:
	Shader(const std::string& shaderFilePath);
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

private:
	ShaderProgramSource ParseShader(const std::string& filePath);
	ShaderProgramSource LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	unsigned int CreateShaderProgram(const ShaderProgramSource& shaderSource);
	unsigned int CompileShader(unsigned int type, const std::string& source);

	int GetUniformLocation(const std::string& name);

public: //Uniform functions
	//Floats
	void SetUniform1f(const std::string& name, float f);
	void SetUniform2f(const std::string& name, float v0, float v1);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

	//Ints
	void SetUniform1i(const std::string& name, int v0);

	//Float Vectors
	//void SetUniform2fv(const std::string& name, float* fv);
	//void SetUniform3fv(const std::string& name, float* fv);
	//void SetUniform4fv(const std::string& name, float* fv);

	//Matrix
	//void SetUniformMatrix4f(const std::string& name, const void* mat);


	//GLM Matrix
	void SetUniformMatrix4f(const std::string& name, glm::mat4& mat);
};

