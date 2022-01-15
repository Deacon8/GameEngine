#include <stdio.h>
#include "engine.h"

int main()
{	
	LoadGLFW();
	LoadOpengl();

	Camera camera = CreateCamera(HMM_Vec3(0, 0, -100), HMM_Vec3(0, 0, 0), HMM_ToRadians(45), (float)800/(float)600, 0.1f, (float)500);

	Entity entity;
	entity.transform = CreateNewTransform();
	entity.renderer.hastexture = 1;
	entity.renderer.texture = LoadTexture("res/models/cat.jpg");
	scale(&entity.transform, HMM_Vec3(1, 1, 1));
	entity.renderer.model = LoadOBJ("res/models/sphere.obj");
	entity.renderer.shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/texture.frag");

	Entity two;
	two.transform = CreateNewTransform();
	translate(&two.transform, HMM_Vec3(0, 1, 0));
	scale(&two.transform, HMM_Vec3(0.1, 0.1, 0.1));
	two.renderer.model = LoadOBJ("res/models/monkey.obj");
	two.renderer.shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/color.frag");
	SetUniformVec3(two.renderer.shader, "incolor", HMM_Vec3(1, 0, 0));
	

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
		if (glfwGetKey(window, GLFW_KEY_Z))
		{
			rotate(&entity.transform, HMM_Vec3(-0, 0.001, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_X))
		{
			rotate(&entity.transform, HMM_Vec3(0, -0.001, 0));
		}
		PreDraw();

		DrawEntity(entity, camera);
		DrawEntity(two, camera);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	glfwTerminate();
	
	return(0);
}