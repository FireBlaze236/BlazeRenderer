#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Window
{

private:
	GLFWwindow* m_Window;

public:
	Window();
	Window(int width, int height, const char* title, bool fs, bool core, int vMaj, int vMin);
	~Window();

	void MakeCurrent();
	bool isClosing();

	void PollEvents();
	void SwapBuffers();

	void AttachResizeCallback(GLFWwindowsizefun func);

};

