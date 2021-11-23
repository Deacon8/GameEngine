#pragma once
#include <stdlib.h>

#define MaxShaderSize 150


struct Shader
{	
	unsigned int VertexShader;
	unsigned int FragmentShader;
	
	unsigned int ShaderProgram;
};
typedef struct Shader Shader;

void LoadShaderSource(char* destination, char* path);

//Possibly combine at some point
unsigned int LoadVertexShader(const char* source);
unsigned int LoadFragmentShader(const char* source);

unsigned int LinkShaders(unsigned int vertexShader, unsigned int fragmentShader);

void DeleteShader(unsigned int shader);

Shader LazyLoadShader(char* VertexShaderPath, char* FragmentShaderPath);

