#pragma once
#include "HandmadeMath.h"
struct model
{
	hmm_vec3* vertices;
	int vsize;
	
	hmm_vec2* uvs;
	int usize;
	
	hmm_vec3* normals;
	int nsize;
	
	unsigned int* vindices;
	int visize;

	unsigned int* uindices;
	int uisize;

	unsigned int* nindices;
	int nisize;
};
typedef struct model model;

model LoadOBJ(char* path);