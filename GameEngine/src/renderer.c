#include "texture.h"
#include "renderer.h"
#include "transform.h"
#include "entity.h"
#include "glad/glad.h"
#include <stdio.h>
//#include "glfw/glfw3.h"

void DrawEntity(Entity entity, Camera camera)
{	
    glUseProgram(entity.renderer.shader.ShaderProgram);
	switch(entity.renderer.shadertype)
	{
		case basic_color:
		SetUniformVec3(entity.renderer.shader, "incolor", entity.renderer.color);
		//printf("2 %i\n", glGetError());
		break;
		case basic_texture:
		SetTexture(entity.renderer.texture, 0);
		SetUniformSampler2D(entity.renderer.shader, "intexture", 0);
		break;
	}
	//printf("%i\n", glGetError());
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