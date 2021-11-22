#pragma once
struct Shader
{	
	unsigned int VertexShader;
	unsigned int FragmentShader;
	
	unsigned int ShaderProgram;
	
	char* VertexShaderSource;
	char* FragmentShaderSource;
};

char* LoadShaderSource(char* path);

//Possibly combine at some point
unsigned int LoadVertexShader(char* source);
unsigned int LoadFragmentShader(char* source);

unsigned int LinkShaders(unsigned int vertexShader, unsigned int fragmentShader);

void DeleteShaders(unsigned int shader);