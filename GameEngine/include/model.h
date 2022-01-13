#pragma once
#include "HandmadeMath.h"
struct Model
{
	hmm_vec3* vertices;
	int vsize;
	
	hmm_vec2* uvs;
	int usize;
	
	hmm_vec3* normals;
	int nsize;

	float* all;
	unsigned int allsize;
	
	unsigned int* vindices;
	int visize;

	unsigned int* uindices;
	int uisize;

	unsigned int* nindices;
	int nisize;

	unsigned int* finalindices;
	int fisize;

	unsigned int VAO;
};
typedef struct Model Model;

Model LoadOBJ(char* path);