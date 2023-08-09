#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "MasterRenderer.h"
#include "MouseListener.h"
#include "KeyListener.h"

GLFWwindow* CreateWindow(int width, int height, const char* title);
void SetupWindowCallbacks(MasterRenderer* renderer, GLFWwindow* window);
void WindowSizeCallback(GLFWwindow* window, int width, int height);
