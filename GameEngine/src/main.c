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
	translate(&entity.transform, HMM_Vec3(-5, 0, 0));
	scale(&entity.transform, HMM_Vec3(-0.5, -0.5, -0.5));
	entity.renderer.model = LoadOBJ("res/models/sphere.obj");
	entity.renderer.shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/texture.frag");

	Entity two;
	two.transform = CreateNewTransform();
	translate(&two.transform, HMM_Vec3(5, 0, 0));
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
	Texture cubemap = LoadCubemap
	(
		skyshader,
		"res/images/skybox/right.jpg", 
		"res/images/skybox/left.jpg", 
		"res/images/skybox/top.jpg", 
		"res/images/skybox/bottom.jpg",
		"res/images/skybox/front.jpg", 
		"res/images/skybox/back.jpg");

	translate(&camera.transform, HMM_Vec3(0, 0, -25));
	
	double previousTime = glfwGetTime();
	int frameCount = 0;
	
	camera.projection = HMM_Perspective(45.0f, (float)800/(float)600, 0.1f, 100);
	while(WindowOpen())
	{	
		const float cameraSpeed = 0.05f; // adjust accordingly
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			translateLocal(&camera.transform, Dforward, cameraSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			translateLocal(&camera.transform, Dleft, cameraSpeed);
		}    
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			translateLocal(&camera.transform, Dback, cameraSpeed);
		}    
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			translateLocal(&camera.transform, Dright, cameraSpeed);
		}		
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		{
			rotate(&camera.transform, HMM_Vec3(0, -cameraSpeed, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		{
			rotate(&camera.transform, HMM_Vec3(-cameraSpeed, 0, 0));
		}    
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			rotate(&camera.transform, HMM_Vec3(0, cameraSpeed, 0));
		}    
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		{
			rotate(&camera.transform, HMM_Vec3(cameraSpeed, 0, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			camera.zoom-=0.1f;
			camera.projection = HMM_Perspective(camera.zoom, (float)800/(float)600, 0.1f, 100);
			//printf("z: %f\n", zoom);
		}
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{	
			camera.zoom+=0.1f;
			camera.projection = HMM_Perspective(camera.zoom, (float)800/(float)600, 0.1f, 100);
			//printf("z: %f\n", zoom);
		}
		PreDraw();
		DrawCubemap(cubemap, skyshader, camera);

		DrawEntity(entity, camera);
		DrawEntity(two, camera);
		//DrawEntity(plane, camera);

		double currentTime = glfwGetTime();
		frameCount++;
		// If a second has passed.
		if ( currentTime - previousTime >= 1.0 )
		{
			printf("fps: %i\n", frameCount);
			printf("fov: %f\n", camera.zoom);
			printf("pos: %f, %f, %f\n", camera.transform.position.X, camera.transform.position.Y, camera.transform.position.Z);
			printf("rot: %f, %f, %f\n", camera.transform.rotation.X, camera.transform.rotation.Y, camera.transform.rotation.Z);
			hmm_vec3 f = GetFront(camera.transform);
			printf("for: %f, %f, %f\n\n", f.X, f.Y, f.Z);
			frameCount = 0;
			previousTime = currentTime;
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	
	return(0);
}