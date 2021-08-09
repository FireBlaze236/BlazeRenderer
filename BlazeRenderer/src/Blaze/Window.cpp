#include "Window.h"
#include "Logger.h"


Window::Window()
	: m_Window(nullptr)
{
	if (!glfwInit())
	{
		LOG("GLFW INITIALIZATION ERROR");
		ASSERT(false);
	}

	m_Window = glfwCreateWindow(640, 480, "GLFWWindow", NULL, NULL);

	if (!m_Window)
	{
		LOG("GLFW Window creation failed!");
		glfwTerminate();
		ASSERT(false);
	}

	MakeCurrent();
}

Window::Window(int width = 640, int height = 480, const char* title = "Window",
	bool resizable = true, bool fullscreen = false, bool core = false,
	int majVersion = 3, int minVersion = 3)
{
	if (!glfwInit())
	{
		LOG("GLFW INITIALIZATION ERROR");
		ASSERT(false);
	}

	//CREATE VERSION
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minVersion);

	//IF CORE
	if (core)
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	else
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	//


	//IF FULLSCREEM
	if (fullscreen)
		m_Window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
	else
	{
		//RESIZABLE
		if (resizable)
		{
			glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
			glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
				{
					glfwSetWindowSize(window, width, height);
				}
			);
		}
		m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
	}
		

	if (!m_Window)
	{
		LOG("GLFW Window creation failed!");
		glfwTerminate();
		ASSERT(false);
	}

	MakeCurrent();


}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	
}

void Window::MakeCurrent()
{
	glfwMakeContextCurrent(m_Window);
}


bool Window::isClosing()
{
	return glfwWindowShouldClose(m_Window);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_Window);
}





