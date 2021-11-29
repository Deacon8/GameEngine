#pragma once
struct model
{
	float vertices*;
	int vsize;
	unsigned int indices*;
	int isize;
};
typedef struct model model;

model LoadOBJ(char* path);