#include "Shader.h"
#include "Logger.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>


Shader::Shader(std::string& shaderFilePath)
	:m_RendererID(0)
{
	m_Filepath = shaderFilePath;
	
	ShaderProgramSource shaderSource = ParseShader(shaderFilePath);

	m_RendererID = CreateShaderProgram(shaderSource);
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
	std::string vertexSource;
	std::string fragmentSource;

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::ifstream file(filePath);
	
	std::string line;
	std::stringstream ss[2];

	ShaderType type = ShaderType::NONE;

	while (std::getline(file, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };

}

unsigned int Shader::CreateShaderProgram(const ShaderProgramSource& shaderSource)
{
	GLCall(unsigned int program = glCreateProgram());

	unsigned int vs = CompileShader(GL_VERTEX_SHADER, shaderSource.VertexSource);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, shaderSource.FragmentSource);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));


	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));
	
	return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	GLCall(unsigned int id = glCreateShader(type));

	const char* src = source.c_str();

	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		
		char buffer[1024];
		GLCall(glGetShaderInfoLog(id, 1024, NULL, buffer));
		std::string log(buffer);

		LOG("Failed to compile shader : " + std::to_string(id) + "\n");
		LOG(log);

		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;

}






Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}


int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformMap.find(name) != m_UniformMap.end())
	{
		return m_UniformMap[name];
	}

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
	{
		LOG("Warning! " + name + " does not exist!");
	}

	m_UniformMap[name] = location;
	return location;
}

//Unform Functions

void Shader::SetUniform1f(const std::string& name, float f)
{
	GLCall(glUniform1f(GetUniformLocation(name), f));
}

void Shader::SetUniform2f(const std::string& name, float v0, float v1)
{
	GLCall(glUniform2f(GetUniformLocation(name), v0, v1));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

