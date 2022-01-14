#include "renderer.h"
#include "entity.h"
#include "glad/glad.h"
//#include "glfw/glfw3.h"

void DrawEntity(Renderer renderer, Camera camera)
{
    glUseProgram(renderer.shader.ShaderProgram);

	SetTexture(texture, 0);
	SetUniformSampler2D(renderer.shader, "intexture", 0);

	SetUniformMat4(renderer.shader, "model", entity.transform.final);
	SetCameraUniforms(renderer.shader, camera);

    glBindVertexArray(renderer.model.VAO);
	glDrawArrays(GL_TRIANGLES, 0, renderer.model.visize);
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