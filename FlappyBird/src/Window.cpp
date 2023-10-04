#include "Window.h"

GLFWwindow* window = NULL;

GLFWwindow* CreateWindow(int width, int height, const char* title)
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw\n";
		return nullptr;
	}

	window = glfwCreateWindow(1280, 720, "ClickyPicky", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create window\n";
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glfwSwapInterval(1);

	return window;
}

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	MasterRenderer* renderer = (MasterRenderer*)glfwGetWindowUserPointer(window);
	renderer->CreateProjectionMatrix();
}

void OnWindowPosChanged(GLFWwindow* window, int xpos, int ypos)
{
	Manager* mgr = (Manager*)glfwGetMonitorUserPointer(glfwGetPrimaryMonitor());
	//mgr->TriggerUpdatePaused();
}

void SetupWindowCallbacks(MasterRenderer* renderer, Manager* mgr)
{
	glfwSetWindowUserPointer(window, renderer);
	glfwSetMonitorUserPointer(glfwGetPrimaryMonitor(), mgr);
	glfwSetWindowSizeCallback(window, WindowSizeCallback);

	glfwSetKeyCallback(window, KeyListener::KeyCallback);
	glfwSetMouseButtonCallback(window, MouseListener::MouseButtonCallback);
	glfwSetCursorPosCallback(window, MouseListener::MousePosCallback);
	glfwSetScrollCallback(window, MouseListener::MouseScrollCallback);

	glfwSetWindowPosCallback(window, OnWindowPosChanged);
}
