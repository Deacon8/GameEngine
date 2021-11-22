#include "shader.h"
#include "glad/glad.h"
#include "stdio.h"

//Malloc from here?? Probably bad idea.
void LoadShaderSource(char* destination, char* path)
{
	FILE* file;
	file = fopen(path, "r");
	int elementCount;
	
	fseek (file , 0 , SEEK_END);
	elementCount = ftell (file);
	rewind (file);
	
	destination = (char*)malloc(sizeof(char) * elementCount);
	
	fread(destination, 1, elementCount, file);
	
	fclose(file);
}

//Possibly combine at some point
unsigned int LoadVertexShader(char* source)
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
	return vertexShader;
}

unsigned int LoadFragmentShader(char* source)
{
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
	return fragmentShader;
}

unsigned int LinkShaders(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
	return shaderProgram;
}

void DeleteShaders(unsigned int shader)
{
	glDeleteShader(shader);
}