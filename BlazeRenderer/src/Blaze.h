#pragma once
#include "Blaze/Logger.h"

#include "Blaze/Window.h"
#include "Blaze/Renderer.h"
#include "Blaze/Texture.h"

#include "Blaze/Renderer.h"


//Utility function definitions 
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

void ResizeWindowCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}