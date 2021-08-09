#include <iostream>
#include <glad/glad.h>

#include "Blaze/Logger.h"
#include "Blaze/Window.h"
#include "Blaze/VertexArray.h"



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
	Window* win = new Window();

	gladLoadGL();
	
	float vertices[] = {
		-0.5f, 0.0f, 0.0f,
		 0.5f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2
	};

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

	


	GLCall(glClearColor(0.5f, 0.3f, 0.3f, 1.0f));

	while (!win->isClosing())
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		vertexArray.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));
		glDrawArrays(GL_TRIANGLES, 0, 3);

		win->PollEvents();
		win->SwapBuffers();
	}

	//CLEAN UP
	delete win;
}
