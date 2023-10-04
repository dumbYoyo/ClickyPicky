#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "MasterRenderer.h"
#include "MouseListener.h"
#include "KeyListener.h"
#include "Manager.h"

GLFWwindow* CreateWindow(int width, int height, const char* title);
/// <summary>
/// This should be called in the scene that is first created by the manager.
/// </summary>
/// <param name="renderer: for updating projection matrix when window is resized"></param>
/// <param name="mgr: TODO"></param>
void SetupWindowCallbacks(MasterRenderer* renderer, Manager* mgr);
void OnWindowPosChanged(GLFWwindow* window, int xpos, int ypos);
void WindowSizeCallback(GLFWwindow* window, int width, int height);
