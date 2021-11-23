#include "shader.h"
#include "glad/glad.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//Malloc from here?? Probably bad idea.
void LoadShaderSource(char* destination, char* path)
{
	FILE* file;
	file = fopen(path, "r");
	int elementCount;
	
	fseek (file , 0 , SEEK_END);
	elementCount = ftell (file);
	rewind (file);
	
	char tempSource[elementCount];
	
	fread(&tempSource[0], 1, elementCount, file);
	//printf("%s", &tempSource[0]);
	destination = malloc(elementCount);
	strcpy(destination, tempSource);
	
	fclose(file);
}

void CheckCompile(unsigned int shader)
{
	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		printf("Compile Error");
		return;
	}
}

void CheckLink(unsigned int program)
{
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		printf("Link Error");
		return;
	}
}

//Possibly combine at some point
unsigned int LoadVertexShader(const char* source)
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &source, NULL);
    glCompileShader(vertexShader);
	CheckCompile(vertexShader);
	return vertexShader;
}

unsigned int LoadFragmentShader(const char* source)
{
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &source, NULL);
    glCompileShader(fragmentShader);
	CheckCompile(fragmentShader);
	return fragmentShader;
}

unsigned int LinkShaders(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
	CheckLink(shaderProgram);
	return shaderProgram;
}

void DeleteShader(unsigned int shader)
{
	glDeleteShader(shader);
}