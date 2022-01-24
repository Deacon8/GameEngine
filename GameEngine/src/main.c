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
	entity.renderer.texture = LoadTexture("res/models/StarSparrow_Red.png");
	//translate(&entity.transform, HMM_Vec3(0, 0, 10));
	scale(&entity.transform, HMM_Vec3(-0.5, -0.5, -0.5));
	entity.renderer.model = LoadOBJ("res/models/StarSparrow.obj");
	entity.renderer.shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/texture.frag");

	Entity two;
	two.transform = CreateNewTransform();
	translate(&two.transform, HMM_Vec3(5, 0, 0));
	scale(&two.transform, HMM_Vec3(0.5, 0.5, 0.5));
	two.renderer.shadertype = basic_color;
	two.renderer.color = HMM_Vec3(1, 0, 0);
	two.renderer.model = LoadOBJ("res/models/monkey.obj");
	two.renderer.shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/color.frag");

	Entity plane;
	plane.transform = CreateNewTransform();
	translate(&plane.transform, HMM_Vec3(0, 0, 25));
	scale(&plane.transform, HMM_Vec3(10, 10, 10));
	plane.renderer.shadertype = basic_texture;
	plane.renderer.texture = LoadTexture("res/models/planet.jpg");
	plane.renderer.model = LoadOBJ("res/models/sphere.obj");
	plane.renderer.shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/texture.frag");

	Entity funshader;
	funshader.transform = CreateNewTransform();
	translate(&funshader.transform, HMM_Vec3(5, -10, 0));
	scale(&funshader.transform, HMM_Vec3(8, 8, 8));
	funshader.renderer.model = LoadOBJ("res/models/sphere.obj");
	funshader.renderer.shadertype = basic_time;
	funshader.renderer.shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/fun.frag");

	Entity fractal;
	fractal.transform = CreateNewTransform();
	translate(&fractal.transform, HMM_Vec3(-25, 0, 10));
	scale(&fractal.transform, HMM_Vec3(12, 12, 12));
	fractal.renderer.model = LoadOBJ("res/models/sphere.obj");
	fractal.renderer.shadertype = basic_time;
	fractal.renderer.shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/fract.frag");

	Entity cat;
	cat.transform = CreateNewTransform();
	translate(&cat.transform, HMM_Vec3(-10, 5, 50));
	scale(&cat.transform, HMM_Vec3(8, 8, 8));
	cat.renderer.model = LoadOBJ("res/models/cube.obj");
	cat.renderer.shadertype = basic_texture;
	cat.renderer.texture = LoadTexture("res/models/cat.jpg");
	cat.renderer.shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/texture.frag");
	//Skybox
	Shader skyshader = LazyLoadShader("res/shaders/skybox.vert", "res/shaders/skybox.frag");
	Texture cubemap = LoadCubemap
	(
		skyshader,
		"res/images/spacebox/right.jpg", 
		"res/images/spacebox/left.jpg", 
		"res/images/spacebox/top.jpg", 
		"res/images/spacebox/bottom.jpg",
		"res/images/spacebox/front.jpg", 
		"res/images/spacebox/back.jpg");

	translate(&camera.transform, HMM_Vec3(0, 0, -25));
	rotate(&entity.transform, HMM_Vec3(90, 0, 0));
	double previousTime = glfwGetTime();
	int frameCount = 0;
	
	camera.projection = HMM_Perspective(45.0f, (float)800/(float)600, 0.1f, 100);
			float cameraSpeed = 0.05f; // adjust accordingly
	while(WindowOpen())
	{	

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{		
			translateLocal(&entity.transform, Dleft, cameraSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			translateLocal(&entity.transform, Ddown, cameraSpeed);
		}    
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			translateLocal(&entity.transform, Dright, cameraSpeed);
		}    
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			translateLocal(&entity.transform, Dup, cameraSpeed);
		}		
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		{
			rotate(&entity.transform, HMM_Vec3(0, -cameraSpeed, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		{
			rotate(&entity.transform, HMM_Vec3(0, 0, -cameraSpeed));
		}    
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			rotate(&entity.transform, HMM_Vec3(0, cameraSpeed, 0));
		}    
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		{
			rotate(&entity.transform, HMM_Vec3(0, 0, cameraSpeed));
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
		if(glfwGetKey(window, GLFW_KEY_E))
		{
			cameraSpeed += 0.0005;
		}
		if(glfwGetKey(window, GLFW_KEY_Q))
		{
			cameraSpeed -= 0.0005;
		}
		//camera.transform.position = HMM_AddVec3(entity.transform.position, HMM_Vec3(0, 5, -20));
		//camera.transform.rotation = HMM_AddVec3(entity.transform.rotation, HMM_Vec3(-90, 90, 0));
		camera.transform.rotation.Z = entity.transform.rotation.X-90;
		camera.transform.rotation.Y = -entity.transform.rotation.Y+90;
		camera.transform.rotation.X = -entity.transform.rotation.Z;

		//entity.transform.rotation.X = camera.transform.rotation.Z+90;
		//entity.transform.rotation.Y = -camera.transform.rotation.Y+90;
		//entity.transform.rotation.Z = -camera.transform.rotation.X;
		hmm_vec3 campos = GetFront(camera.transform);
		//campos = HMM_Vec3(0, 0, 0);
		//printf("CamPos1: %f %f %f\n", campos.X, campos.Y, campos.Z);
		//printf("CamPos1: %f %f %f\n", camera.transform.position.X, campos.Y, campos.Z);
		//campos.X = campos.X - camera.transform.position.X;
		//campos.Y = campos.Y - camera.transform.position.Y;
		//campos.Z = campos.Z - camera.transform.position.Z;
		//campos = HMM_NormalizeVec3(HMM_Cross(campos, HMM_Vec3(0, 1, 0)));
		camera.transform.position.X = entity.transform.position.X - campos.X*15;
		camera.transform.position.Y = entity.transform.position.Y - campos.Y*15;
		camera.transform.position.Z = entity.transform.position.Z - campos.Z*15;
		//entity.transform.position.X = camera.transform.position.X + campos.X*5;
		//entity.transform.position.Y = camera.transform.position.Y + campos.Y*5;
		//entity.transform.position.Z = camera.transform.position.Z + campos.Z*5;
		camera.transform.position.Y += 3;
		//camera.transform.position.Z -= 10;
		//camera.transform.final = HMM_LookAt(camera.transform.position, entity.transform.position, HMM_Vec3(0, 1, 0));
		//printf("CamPos: %f %f %f\n", campos.X, campos.Y, campos.Z);
		//printf("EPos: %f %f %f\n", entity.transform.position.X, entity.transform.position.Y, entity.transform.position.Z);
		//printf("CamAPos: %f %f %f\n", camera.transform.position.X, camera.transform.position.Y, camera.transform.position.Z);
		//printf("MPos: %f %f %f\n", two.transform.position.X, two.transform.position.Y, two.transform.position.Z);
		PreDraw();
		DrawCubemap(cubemap, skyshader, camera);

		two.transform.position = HMM_Vec3(-24, 0, 0);
		for(int i = -12; i < 12; i++)
		{	
			translate(&two.transform, HMM_Vec3(2, 0, 0));

			DrawEntity(two, camera);
		}
		//printf("EPos: %f %f %f\n", entity.transform.position.X, entity.transform.position.Y, entity.transform.position.Z);
		DrawEntity(entity, camera);
		//printf("EPos: %f %f %f\n", entity.transform.position.X, entity.transform.position.Y, entity.transform.position.Z);
		DrawEntity(plane, camera);
		//translate(&plane.transform, HMM_Vec3(1, 0, 0));
		DrawEntity(funshader, camera);
		//DrawEntity(plane, camera);
		DrawEntity(fractal, camera);

		DrawEntity(cat, camera);

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