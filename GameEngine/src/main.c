#include <stdio.h>
#include "engine.h"

int main()
{	
	LoadGLFW();
	LoadOpengl();

	Camera camera = CreateCamera(HMM_Vec3(0, 0, 0), HMM_Vec3(0, 0, 0), HMM_ToRadians(45), (float)800/(float)600, 0.1f, 100.0f);

	Entity entity;
	entity.transform = CreateNewTransform();
	entity.renderer.shadertype = basic_texture;
	entity.renderer.texture = LoadTexture("res/models/cat.jpg");
	translate(&entity.transform, HMM_Vec3(-10, 0, 0));
	scale(&entity.transform, HMM_Vec3(-0.5, -0.5, -0.5));
	entity.renderer.model = LoadOBJ("res/models/sphere.obj");
	entity.renderer.shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/texture.frag");

	Entity two;
	two.transform = CreateNewTransform();
	translate(&two.transform, HMM_Vec3(10, 0, 0));
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
	//Skybox
	Shader skyshader = LazyLoadShader("res/shaders/skybox.vert", "res/shaders/skybox.frag");
	Texture cubemap = LoadCubemap(skyshader,
		"res/images/skybox/right.jpg", 
		"res/images/skybox/left.jpg", 
		"res/images/skybox/top.jpg", 
		"res/images/skybox/bottom.jpg",
		"res/images/skybox/front.jpg", 
		"res/images/skybox/back.jpg");

	translate(&camera.transform, HMM_Vec3(0, 0, -50));
	while(WindowOpen())
	{	
		if (glfwGetKey(window, GLFW_KEY_W))
		{
			rotate(&camera.transform, HMM_Vec3(0, 0.1, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_A))
		{
			rotate(&camera.transform, HMM_Vec3(-0.1, 0, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_S))
		{
			rotate(&camera.transform, HMM_Vec3(0, -0.1, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_D))
		{
			rotate(&camera.transform, HMM_Vec3(0.001, 0, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_Z))
		{
			rotate(&camera.transform, HMM_Vec3(0, 0, 0.1));
		}
		if (glfwGetKey(window, GLFW_KEY_X))
		{
			rotate(&camera.transform, HMM_Vec3(0, 0, -0.1));
		}
		if (glfwGetKey(window, GLFW_KEY_I))
		{
			translate(&camera.transform, HMM_Vec3(0, 0, 0.1));
		}
		if (glfwGetKey(window, GLFW_KEY_K))
		{
			translate(&camera.transform, HMM_Vec3(0, 0, -0.1));
		}
		if (glfwGetKey(window, GLFW_KEY_I))
		{
			
		}
		PreDraw();
		//DrawCubemap(cubemap, skyshader, camera);

		DrawEntity(entity, camera);
		DrawEntity(two, camera);
		//DrawEntity(plane, camera);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	
	return(0);
}