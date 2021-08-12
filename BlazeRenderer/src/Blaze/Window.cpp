#include "Window.h"
#include "Logger.h"

//Static camera
Camera Window::camera(glm::vec3(0.0, 0.0, 3.0));
float Window::lastX = 320, Window::lastY = 240;
bool Window::firstMouse = true;
//Camera Input functions
void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (Window::firstMouse)
	{
		Window::lastX = xpos;
		Window::lastY = ypos;
		Window::firstMouse = false;
	}

	float xoffset = xpos - Window::lastX;
	float yoffset = Window::lastY - ypos; // reversed since y-coordinates go from bottom to top

	Window::lastX = xpos;
	Window::lastY = ypos;

	Window::camera.ProcessMouseMovement(xoffset, yoffset);
}





//Window class functions
Window::Window()
	: m_Window(nullptr), lastFrame(0), deltaTime (0)
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

Window::Window(int width = 640, int height = 480, const char* title = "Window", bool fullscreen = false, bool core = false,
	int majVersion = 3, int minVersion = 3)
	:lastFrame(0), deltaTime(0)
{
	if (!glfwInit())
	{
		LOG("GLFW INITIALIZATION ERROR");
		ASSERT(false);
	}

	//IF CORE
	if (core)
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	else
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);


	//CREATE VERSION
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minVersion);

	
	//IF FULLSCREEM
	if (fullscreen)
		m_Window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
	else
	{
		m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
	}
		

	if (!m_Window)
	{
		LOG("GLFW Window creation failed!");
		glfwTerminate();
		ASSERT(false);
	}

	MakeCurrent();

	lastX = width / 2.0f;
	lastY = height / 2.0f;
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

void Window::ProcessInput()
{
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_Window, true);

	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);

	if (glfwGetKey(m_Window, GLFW_KEY_C) == GLFW_PRESS)
	{
		AttachMouseCallback(MouseCallback);
	}
	else if (glfwGetKey(m_Window, GLFW_KEY_X) == GLFW_PRESS)
	{
		DetachMouseCallback();
	}
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::SwapBuffers()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glfwSwapBuffers(m_Window);
}

void Window::AttachResizeCallback(GLFWwindowsizefun func)
{
	glfwSetWindowSizeCallback(m_Window, func);
}

void Window::AttachMouseCallback(GLFWcursorposfun func)
{
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(m_Window, func);
}

void Window::DetachMouseCallback()
{
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPosCallback(m_Window, NULL);
}



