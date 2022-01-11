#include <stdio.h>
#include "glad/glad.h"
//unnecessary??
//#define GLFW_DLL
#include "glfw/glfw3.h"

#include "HandmadeMath.h"
#include "stb_image.h"

#include "memory.h"
#include "shader.h"
#include "model.h"
#include "camera.h"
#include "texture.h"

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
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);  
	glDisable(GL_CULL_FACE); 
	//glDisable(GL_ALPHA_TEST); 
	//glViewport(0, 0, 800, 600);
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetErrorCallback(ErrorCallback);
	
	Camera camera = newCamera(HMM_Vec3(0, 0, -100));

	Shader shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/texture.frag");
	//Shader shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/crazy.frag");
	//SetUniformFloat(shader, "time", 0.0f);

	Texture texture = LoadTexture("res/models/cat.jpg");

	//Local Transform of GO
	hmm_mat4 transform = HMM_Rotate(HMM_ToRadians(45), HMM_Vec3(1, 0, 0));

	//printf("as");
	model test = LoadOBJ("res/models/cube.obj");
	//printf("asdf");
	for(int i = 0; i < test.visize; i++)
	{
		printf("v%f, %f, %f, u%f, %f, n%f, %f, %f, %u, %u, %u\n"
		, test.vertices[i].Elements[0], test.vertices[i].Elements[1], test.vertices[i].Elements[2]
		, test.uvs[i].Elements[0], test.uvs[i].Elements[1]
		, test.normals[i].Elements[0], test.normals[i].Elements[1], test.normals[i].Elements[2]
		, test.vindices[i], test.uindices[i], test.nindices[i]);
	}

    unsigned int VAO, EBO;
	unsigned int vbuffer, ubuffer, nbuffer;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &vbuffer);
	glGenBuffers(1, &ubuffer);
	glGenBuffers(1, &nbuffer);
	glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
	
	//printf("\naksnklas: %u\n", test.visize);
	//printf("aksnklas: %u\n", test.vsize);

	//Using STATIC DRAW
    glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
    glBufferData(GL_ARRAY_BUFFER, (test.visize) * sizeof(hmm_vec3), &test.vertices->Elements[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, ubuffer);
    glBufferData(GL_ARRAY_BUFFER, (test.uisize) * sizeof(hmm_vec2), &test.uvs->Elements[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, nbuffer);
    glBufferData(GL_ARRAY_BUFFER, (test.nisize) * sizeof(hmm_vec3), &test.normals->Elements[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, test.visize * sizeof(unsigned int), &test.vindices[0], GL_STATIC_DRAW);
	//is this local or global?
	//vert
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
	//uv
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
	//normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
	//

	//Unneccessary
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
	printf("gwewe");
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader.ShaderProgram);
		//
		SetTexture(texture, 0);		
		SetUniformSampler2D(shader, "intexture", 0);
		transform = HMM_Rotate(HMM_ToRadians(glfwGetTime() * 1000), HMM_Vec3(0, 1, 0));;
		//transform = HMM_Mat4();
		//camera.view = translateCamera(&camera, HMM_Vec3(0, 0, -0.01));
		SetCamPos(&camera, HMM_Vec3(0, 0, -100));
		SetUniformMat4(shader, "model", transform);
		SetCameraUniforms(shader, camera);
        glBindVertexArray(VAO);
		//float* data = malloc(sizeof(int) * 12);
		//glGetBufferSubData(GL_ARRAY_BUFFER, 0, 12, data);
		//for(int i = 0; i < 12; i++)
		//{
		//	printf("D: %f\n", data[i]);
		//}
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
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