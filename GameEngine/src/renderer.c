#include "texture.h"
#include "renderer.h"
#include "transform.h"
#include "entity.h"
#include "glad/glad.h"
#include <stdio.h>
//#include "glfw/glfw3.h"

void DrawEntity(Entity entity, Camera camera)
{	
	//printf("%i\n", entity.renderer.shader.ShaderProgram);
    glUseProgram(entity.renderer.shader.ShaderProgram);
	//printf("%i\n", glGetError());
	if(entity.renderer.hastexture)
	{
		SetTexture(entity.renderer.texture, 0);
		SetUniformSampler2D(entity.renderer.shader, "intexture", 0);
	}
	//printf("2%i\n", glGetError());
	SetUniformMat4(entity.renderer.shader, "model", entity.transform.final);
	SetCameraUniforms(entity.renderer.shader, camera);
	//printf("3%i\n", glGetError());
    glBindVertexArray(entity.renderer.model.VAO);
	glDrawArrays(GL_TRIANGLES, 0, entity.renderer.model.visize);
	//printf("4%i\n", glGetError());
}

void PreDraw()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //More?
}

void PostDraw()
{

}