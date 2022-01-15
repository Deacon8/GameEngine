#pragma once
#include <stdlib.h>
#include "camera.h"


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

void SetUniformFloat(Shader shader, const char* name, float value);
void SetUniformVec3(Shader shader, const char* name, hmm_vec3 value);
void SetUniformMat4(Shader shader, const char* name, hmm_mat4 value);
void SetCameraUniforms(Shader shader, Camera camera);
void SetUniformSampler2D(Shader shader, const char* name, unsigned int unit);

Shader LazyLoadShader(char* VertexShaderPath, char* FragmentShaderPath);

