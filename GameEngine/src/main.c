#include <stdio.h>
#include "engine.h"

int main()
{	
	LoadGLFW();
	LoadOpengl();

	Camera camera = CreateCamera(HMM_Vec3(0, 0, -50), HMM_Vec3(0, 0, 0), HMM_ToRadians(45), (float)800/(float)600, 0.1f, 100.0f);

	Entity entity;
	entity.transform = CreateNewTransform();
	entity.renderer.shadertype = basic_texture;
	entity.renderer.texture = LoadTexture("res/models/cat.jpg");
	translate(&entity.transform, HMM_Vec3(-1, 0, 0));
	scale(&entity.transform, HMM_Vec3(-0.5, -0.5, -0.5));
	entity.renderer.model = LoadOBJ("res/models/sphere.obj");
	entity.renderer.shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/texture.frag");

	Entity two;
	two.transform = CreateNewTransform();
	translate(&two.transform, HMM_Vec3(1, 0, 0));
	scale(&two.transform, HMM_Vec3(-0.5, -0.5, -0.5));
	two.renderer.shadertype = basic_color;
	two.renderer.color = HMM_Vec3(1, 0, 0);
	two.renderer.model = LoadOBJ("res/models/monkey.obj");
	two.renderer.shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/color.frag");

	Entity plane;
	plane.transform = CreateNewTransform();
	translate(&plane.transform, HMM_Vec3(0, -50, 0));
	scale(&plane.transform, HMM_Vec3(1, 1, 1));
	plane.renderer.shadertype = basic_color;
	plane.renderer.color = HMM_Vec3(0.9, 0.9, 0.9);
	plane.renderer.model = LoadOBJ("res/models/cube.obj");
	plane.renderer.shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/color.frag");
	//Extra Data
const static float skyboxVertices[] = 
{
    // positions          
  -10.0f,  10.0f, -10.0f,
  -10.0f, -10.0f, -10.0f,
   10.0f, -10.0f, -10.0f,
   10.0f, -10.0f, -10.0f,
   10.0f,  10.0f, -10.0f,
  -10.0f,  10.0f, -10.0f,
  
  -10.0f, -10.0f,  10.0f,
  -10.0f, -10.0f, -10.0f,
  -10.0f,  10.0f, -10.0f,
  -10.0f,  10.0f, -10.0f,
  -10.0f,  10.0f,  10.0f,
  -10.0f, -10.0f,  10.0f,
  
   10.0f, -10.0f, -10.0f,
   10.0f, -10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f,  10.0f, -10.0f,
   10.0f, -10.0f, -10.0f,
   
  -10.0f, -10.0f,  10.0f,
  -10.0f,  10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f, -10.0f,  10.0f,
  -10.0f, -10.0f,  10.0f,
  
  -10.0f,  10.0f, -10.0f,
   10.0f,  10.0f, -10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
  -10.0f,  10.0f,  10.0f,
  -10.0f,  10.0f, -10.0f,
  
  -10.0f, -10.0f, -10.0f,
  -10.0f, -10.0f,  10.0f,
   10.0f, -10.0f, -10.0f,
   10.0f, -10.0f, -10.0f,
  -10.0f, -10.0f,  10.0f,
   10.0f, -10.0f,  10.0f
};	
	printf("Test");
	Texture cubemap = LoadCubemap(
		"res/images/skybox/right.jpg", 
		"res/images/skybox/left.jpg", 
		"res/images/skybox/top.jpg", 
		"res/images/skybox/bottom.jpg",
		"res/images/skybox/front.jpg", 
		"res/images/skybox/back.jpg");
	Shader skyshader = LazyLoadShader("res/shaders/skybox.vert", "res/shaders/skybox.frag");
	unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glUseProgram(skyshader.ShaderProgram);
	SetUniformSampler2D(skyshader, "skybox", 0);

	double previousTime = glfwGetTime();
	int frameCount = 0;
	while(WindowOpen())
	{	
		if (glfwGetKey(window, GLFW_KEY_W))
		{
			translate(&camera.transform, HMM_Vec3(0, 0, 0.001));
		}
		if (glfwGetKey(window, GLFW_KEY_A))
		{
			translate(&camera.transform, HMM_Vec3(-0.001, 0, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_S))
		{
			translate(&camera.transform, HMM_Vec3(0, 0, -0.001));
		}
		if (glfwGetKey(window, GLFW_KEY_D))
		{
			translate(&camera.transform, HMM_Vec3(0.001, 0, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_Z))
		{
			rotate(&entity.transform, HMM_Vec3(-0, 0.001, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_X))
		{
			rotate(&entity.transform, HMM_Vec3(0, -0.001, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_C))
		{
			rotate(&camera.transform, HMM_Vec3(0, glfwGetTime(), 0));
		}
		PreDraw();
		glDepthMask(GL_FALSE);  // change depth function so depth test passes when values are equal to depth buffer's content
        glUseProgram(skyshader.ShaderProgram);
        hmm_mat4 view = GetCameraView(camera); // remove translation from the view matrix
		SetUniformMat4(skyshader, "view", view);
		SetUniformMat4(skyshader, "projection", camera.projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap.tex);
		//printf("wf; %i", cubemap.tex);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthMask(GL_TRUE);
		//rotate(&camera.transform, HMM_Vec3(0, 0.1, 0));
		double currentTime = glfwGetTime();
		frameCount++;
		// If a second has passed.
		if ( currentTime - previousTime >= 1.0 )
		{
			// Display the frame count here any way you want.
			printf("%i\n", frameCount);

			frameCount = 0;
			previousTime = currentTime;
		}
		DrawEntity(entity, camera);
		DrawEntity(two, camera);
		//DrawEntity(plane, camera);
/*
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        glUseProgram(skyshader.ShaderProgram);
        hmm_mat4 view = GetCameraView(camera); // remove translation from the view matrix
		SetUniformMat4(skyshader, "view", view);
		SetUniformMat4(skyshader, "projection", camera.projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap.tex);
		//printf("wf; %i", cubemap.tex);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
*/
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	glfwTerminate();
	
	return(0);
}