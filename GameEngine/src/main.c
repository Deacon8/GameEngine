#include <stdio.h>
#include "glad/glad.h"
#define GLFW_DLL
#include "glfw/glfw3.h"

#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  

int main()
{
	//Create Window
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Game Engine", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) 
	{	
		glfwTerminate();
        return -1;
    }
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//ShaderStuff
	Shader shader;
	LoadShaderSource(shader.VertexShaderSource, "res/shaders/basic.vert");
	LoadShaderSource(shader.FragmentShaderSource, "res/shaders/basic.frag");
	printf("%s", shader.VertexShaderSource);
	shader.VertexShader = LoadVertexShader((const char*)shader.VertexShaderSource);
	shader.FragmentShader = LoadFragmentShader((const char*)shader.FragmentShaderSource);
	shader.ShaderProgram = LinkShaders(shader.VertexShader, shader.FragmentShader);
	DeleteShader(shader.VertexShader);
	DeleteShader(shader.FragmentShader);
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

	while(!glfwWindowShouldClose(window))
	{	
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader.ShaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	printf("Done");
	glfwTerminate();
	
	return(0);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  