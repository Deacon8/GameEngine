#include "shader.h"
#include "glad/glad.h"
#include <stdio.h>
#include "memory.h"
#include "camera.h"

void LoadShaderSource(char* destination, char* path)
{	
	FILE* file = fopen(path, "r");
	if (file != NULL) 
	{
		size_t newLen = fread(destination, sizeof(char), GetFileSize(path), file);
		if ( ferror( file ) != 0 ) 
		{
			fputs("Error reading file", stderr);
		} 
		else 
		{
			destination[newLen++] = '\0';
		}

		fclose(file);
	}
}

GLint CheckCompile(unsigned int shader)
{
	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	return isCompiled;
}

GLint CheckLink(unsigned int program)
{
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	return isLinked;
}

//Possibly combine at some point
unsigned int LoadVertexShader(const char* source)
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &source, NULL);
    glCompileShader(vertexShader);
	if(CheckCompile(vertexShader) == GL_FALSE)
	{
		printf("Vertex Compile Error");
	}
	return vertexShader;
}

unsigned int LoadFragmentShader(const char* source)
{
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &source, NULL);
    glCompileShader(fragmentShader);
	if(CheckCompile(fragmentShader) == GL_FALSE)
	{
		printf("Fragment Compile Error");
	}
	return fragmentShader;
}

unsigned int LinkShaders(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
	if(CheckLink(shaderProgram) == GL_FALSE)
	{
		printf("Link Error");
	}
	return shaderProgram;
}

void DeleteShader(unsigned int shader)
{
	glDeleteShader(shader);
}

void SetUniformFloat(Shader shader, const char* name, float value)
{
	int location = glGetUniformLocation(shader.ShaderProgram, name);
	glUseProgram(shader.ShaderProgram);
	glUniform1f(location, value);
}

void SetUniformVec3(Shader shader, const char* name, hmm_vec3 value)
{
	int location = glGetUniformLocation(shader.ShaderProgram, name);
	glUseProgram(shader.ShaderProgram);
	glUniform3fv(location, 3, &value.Elements[0]);
}

void SetUniformMat4(Shader shader, const char* name, hmm_mat4 value)
{
	int location = glGetUniformLocation(shader.ShaderProgram, name);
	glUseProgram(shader.ShaderProgram);
	glUniformMatrix4fv(location, 1, GL_FALSE, (const GLfloat*)(&value.Elements[0]));
}

void SetCameraUniforms(Shader shader, Camera camera)
{
	//int modelloc = glGetUniformLocation(shader.ShaderProgram, "model");
	int viewloc = glGetUniformLocation(shader.ShaderProgram, "view");
	int projloc = glGetUniformLocation(shader.ShaderProgram, "projection");
	glUseProgram(shader.ShaderProgram);
	//glUniformMatrix4fv(modelloc, 1, GL_FALSE, &camera.model.Elements[0]);
	glUniformMatrix4fv(viewloc, 1, GL_FALSE, (const GLfloat*)&camera.transform.final.Elements[0]);
	glUniformMatrix4fv(projloc, 1, GL_FALSE, (const GLfloat*)&camera.projection.Elements[0]);
}

void SetUniformSampler2D(Shader shader, const char* name, unsigned int unit)
{
	GLint loc = glGetUniformLocation(shader.ShaderProgram, name);
	glUseProgram(shader.ShaderProgram);
	glUniform1i(loc, unit);
}

Shader LazyLoadShader(char* VertexShaderPath, char* FragmentShaderPath)
{	
	Shader shader;
	int vsize = GetFileSize(VertexShaderPath)+1;
	int fsize = GetFileSize(FragmentShaderPath)+1;
	char* BasicVertex = malloc(vsize);
	char* BasicFragment = malloc(fsize);
	LoadShaderSource(BasicVertex, VertexShaderPath);
	LoadShaderSource(BasicFragment, FragmentShaderPath);
	
	shader.VertexShader = LoadVertexShader((const char*)BasicVertex);
	shader.FragmentShader = LoadFragmentShader((const char*)BasicFragment);
	shader.ShaderProgram = LinkShaders(shader.VertexShader, shader.FragmentShader);

	DeleteShader(shader.VertexShader);
	DeleteShader(shader.FragmentShader);
	
	return shader;
}