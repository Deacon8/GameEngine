#include <stdio.h>
#include "engine.h"

int main()
{	
	LoadGLFW();
	LoadOpengl();
	//HMM_qua
	Entity entity;
	entity.transform = CreateNewTransform();
	scale(&entity.transform, HMM_Vec3(10, 10, 10));
	entity.renderer.model = LoadOBJ("res/models/monkey.obj");
	entity.renderer.shader = LazyLoadShader("res/shaders/basic.vert", "res/shaders/texture.frag");
	
	Camera camera = CreateCamera(HMM_Vec3(0, 0, -100), HMM_Vec3(0, 0, 0), HMM_ToRadians(45), (float)800/(float)600, 0.1f, (float)500);

	Texture texture = LoadTexture("res/models/cat.jpg");

	while(WindowOpen())
	{	

		PreDraw();

		glUseProgram(entity.renderer.shader.ShaderProgram);

		SetTexture(texture, 0);
		SetUniformSampler2D(entity.renderer.shader, "intexture", 0);

		SetUniformMat4(entity.renderer.shader, "model", entity.transform.final);
		SetCameraUniforms(entity.renderer.shader, camera);

        glBindVertexArray(entity.renderer.model.VAO);
		glDrawArrays(GL_TRIANGLES, 0, entity.renderer.model.visize);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	glfwTerminate();
	
	return(0);
}