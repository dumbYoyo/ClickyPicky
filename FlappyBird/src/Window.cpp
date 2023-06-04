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
