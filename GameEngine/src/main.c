#include <stdio.h>
#include "engine.h"

int main()
{	
	LoadGLFW();
	LoadOpengl();

	Camera camera = CreateCamera(HMM_Vec3(0, 0, -100), HMM_Vec3(0, 0, 0), HMM_ToRadians(45), (float)800/(float)600, 0.1f, (float)500);
	//HMM_qua
	Entity entity;
	entity.transform = CreateNewTransform();
	entity.renderer.hastexture = 1;
	entity.renderer.texture = LoadTexture("res/models/cat.jpg");
	scale(&entity.transform, HMM_Vec3(1, 1, 1));
	entity.renderer.model = LoadOBJ("res/models/monkey.obj");
	entity.renderer.shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/texture.frag");

	Entity two;// = entity;
	two.transform = CreateNewTransform();
	two.renderer.hastexture = 1;
	two.renderer.texture = LoadTexture("res/models/cat.jpg");
	translate(&two.transform, HMM_Vec3(0, 1, 0));
	scale(&two.transform, HMM_Vec3(1, 1, 1));
	two.renderer.model = LoadOBJ("res/models/monkey.obj");
	two.renderer.shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/texture.frag");



	while(WindowOpen())
	{	

		if (glfwGetKey(window, GLFW_KEY_D))
		{
			translate(&entity.transform, HMM_Vec3(-0.001, 0, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_A))
		{
			translate(&entity.transform, HMM_Vec3(0.001, 0, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_W))
		{
			scale(&entity.transform, HMM_Vec3(0.001, 0.001, 0.001));
		}
		if (glfwGetKey(window, GLFW_KEY_S))
		{
			scale(&entity.transform, HMM_Vec3(-0.001, -0.001, -0.001));
		}
		if (glfwGetKey(window, GLFW_KEY_J))
		{
			translate(&camera.transform, HMM_Vec3(-0.001, 0, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_I))
		{
			translate(&camera.transform, HMM_Vec3(0, 0.001, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_K))
		{
			translate(&camera.transform, HMM_Vec3(0, -0.001, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_L))
		{
			translate(&camera.transform, HMM_Vec3(0.001, 0, 0));
		}

		PreDraw();

		DrawEntity(entity, camera);
		//printf("%i", glGetError());

		glfwSwapBuffers(window);
		

		glfwPollEvents();
	}
	glfwTerminate();
	
	return(0);
}