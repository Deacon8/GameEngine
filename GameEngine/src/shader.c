#include "shader.h"
#include "glad/glad.h"
#include <stdio.h>

void LoadShaderSource(char* destination, char* path)
{	
	FILE* file = fopen(path, "r");
	if (file != NULL) 
	{
		size_t newLen = fread(destination, sizeof(char), MaxShaderSize, file);
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

Shader LazyLoadShader(char* VertexShaderPath, char* FragmentShaderPath)
{	
	Shader shader;
	
	char* BasicVertex = malloc(MaxShaderSize);
	char* BasicFragment = malloc(MaxShaderSize);
	LoadShaderSource(BasicVertex, VertexShaderPath);
	LoadShaderSource(BasicFragment, FragmentShaderPath);
	
	shader.VertexShader = LoadVertexShader((const char*)BasicVertex);
	shader.FragmentShader = LoadFragmentShader((const char*)BasicFragment);
	shader.ShaderProgram = LinkShaders(shader.VertexShader, shader.FragmentShader);
	
	DeleteShader(shader.VertexShader);
	DeleteShader(shader.FragmentShader);
	
	return shader;
}