#include "Window.h"

GLFWwindow* CreateWindow(int width, int height, const char* title)
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw\n";
		return nullptr;
	}

	GLFWwindow* window = glfwCreateWindow(1280, 720, "ClickyPicky", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create window\n";
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	return window;
}

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	MasterRenderer* renderer = (MasterRenderer*)glfwGetWindowUserPointer(window);
	renderer->CreateProjectionMatrix();
}

void SetupWindowCallbacks(MasterRenderer* renderer, GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, renderer);
	glfwSetWindowSizeCallback(window, WindowSizeCallback);
}
