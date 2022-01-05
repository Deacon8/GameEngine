#include <stdio.h>
#include "glad/glad.h"
//unnecessary??
//#define GLFW_DLL
#include "glfw/glfw3.h"

#include "memory.h"
#include "shader.h"
#include "model.h"
#include "camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void ErrorCallback(int i, const char* err_str);

int main()
{
	//Create Window
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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
	//glViewport(0, 0, 800, 600);
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetErrorCallback(ErrorCallback);
	
	Camera camera = newCamera(HMM_Vec3(0, 0, -100));

	Shader shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/crazy.frag");
	SetUniformFloat(shader, "time", 0.0f);
	
    float vertices[] = 
	{
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] = 
	{  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	//Local Transform of GO
	hmm_mat4 transform = HMM_Rotate(HMM_ToRadians(45), HMM_Vec3(1, 0, 0));
	
	model test = LoadOBJ("res/models/cube.obj");
	printf("vWorks: %i\n", test.vsize);
	printf("iWorks: %i\n", test.visize);
	for(int i = 0; i < test.visize; i++)
	{
		//printf(" %u", test.vindices[i]);//.Elements[0]);
		//printf("V: %f", test.vindices[i].Elements[1]);
		//printf("V: %f\n", test.vindices[i].Elements[2]);
	}

	//printf(test.indices);

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
    glBindVertexArray(VAO);
	
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (test.vsize) * sizeof(hmm_vec3), test.vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, test.visize * sizeof(unsigned int), test.vindices, GL_STATIC_DRAW);
	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
	
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
	
	//printf("Q");

	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader.ShaderProgram);
		SetUniformFloat(shader, "time", glfwGetTime());
		//transform = HMM_Rotate(HMM_ToRadians(glfwGetTime() * 100), HMM_Vec3(0, 0, 1));;
		transform = HMM_Rotate(HMM_ToRadians(glfwGetTime() * 100), HMM_Vec3(0, 1, 0));;
		//printf("-%f-%f-%f-%f", transform.Elements[0][0], transform.Elements[0][1], transform.Elements[0][2], transform.Elements[0][3]);
		camera.view = translateCamera(&camera, HMM_Vec3(0, 0, -0.01));
		SetUniformMat4(shader, "model", transform);
		SetCameraUniforms(shader, camera);
        glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		//Throws Error??
		//printf("F");
		glfwPollEvents();
		//printf("Error: %i",glfwGetError());
		//printf("w");
	}
	printf("Done");
	glfwTerminate();
	
	return(0);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void ErrorCallback(int i, const char* err_str)
{
    printf("GLFW Error: %s", err_str);
}