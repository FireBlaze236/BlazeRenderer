#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Camera.h"

class Window
{

private:
	GLFWwindow* m_Window;
	
	float lastFrame;

	static float lastX, lastY;
	static bool firstMouse;
public:
	
	static Camera camera;
	float deltaTime;

	Window();
	Window(int width, int height, const char* title, bool fs, bool core, int vMaj, int vMin);
	~Window();

	void MakeCurrent();
	bool isClosing();

	void ProcessInput();
	void PollEvents();
	void SwapBuffers();


	void AttachResizeCallback(GLFWwindowsizefun func);
	void AttachMouseCallback(GLFWcursorposfun func);
	void DetachMouseCallback();
	friend void MouseCallback(GLFWwindow* window, double xpos, double ypos);
};

