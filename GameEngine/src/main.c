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
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	glfwTerminate();
	
	return(0);
}