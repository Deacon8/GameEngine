#pragma once
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include <stdbool.h>

//Clean up and turn into Window/Scene Class

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void ErrorCallback(int i, const char* err_str);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void LoadGLFW()
{
    //Create Window
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(800, 600, "Game Engine", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (window == NULL)
	{
		glfwTerminate();
	}
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetErrorCallback(ErrorCallback);
	glfwSetKeyCallback(window, key_callback);
}

bool WindowOpen()
{
    return !glfwWindowShouldClose(window);
}

void LoadOpengl()
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) 
	{	
		glfwTerminate();
    }
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);  
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

//??
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
	{
		switch(key)
		{
			case GLFW_KEY_W:
			break;
			case GLFW_KEY_A:
			break;
			case GLFW_KEY_S:
			break;
			case GLFW_KEY_D:
			break;
		}
	}
}

void ErrorCallback(int i, const char* err_str)
{
    //printf("GLFW Error: %s", err_str);
}