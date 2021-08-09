#include <iostream>
#include <glad/glad.h>

#include "Blaze/Logger.h"
#include "Blaze/Window.h"
#include "Blaze/Renderer.h"


void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL error]" << "(" << std::hex << error << std::dec << ")" << function << " " << file << " " << line << std::endl;
		return false;
	}

	return true;
}




int main()
{
	Window* win = new Window(800, 600, "BlazeRenderer", false, true, 3, 3);

	gladLoadGL();
	
	float vertices[] = {
		-0.5f, 0.0f, 0.0f,
		 0.5f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2
	};

	//Shaders

	std::string s = "res/shaders/defaultShader.shader";
	Shader shader(s);

	//Vertex Arrays
	VertexArray vertexArray;
	vertexArray.Bind();

	//Set buffer
	VertexBuffer vertexBuffer(vertices, sizeof(vertices));

	//Set layout
	VertexBufferLayout layout;
	layout.Push<float>(3);

	//Index Buffer
	ElementBuffer elementBuffer(indices, 3);
	
	//Add buffer with layout
	vertexArray.AddBuffer(vertexBuffer, layout);


	//Add element buffer
	vertexArray.AddElementBuffer(elementBuffer);


	Renderer renderer;
	
	
	
	

	while (!win->isClosing())
	{
		renderer.Clear();

		shader.Bind();
		shader.SetUniform4f("aColor", 0.1f, std::sin(glfwGetTime()), 0.4f, 1.0f);

		renderer.Draw(vertexArray, elementBuffer, shader);

		

		win->PollEvents();
		win->SwapBuffers();
	}

	//CLEAN UP
	delete win;
}


void ResizeWindowCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}