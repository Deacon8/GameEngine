#include "model.h"
#include "memory.h"
#include "HandmadeMath.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//FIX MEMORY - linked list??

model LoadOBJ(char* path)
{	
	//Using this for size
	const int i = GetFileSize(path);
	
	//Fix Sizes
	hmm_vec3 temp_vertices[50];
	unsigned int vindex = 0;
	hmm_vec2 temp_uvs[50];
	unsigned int uindex = 0;
	hmm_vec3 temp_normals[50];
	unsigned int nindex = 0;
	
	unsigned int vertexIndices[500];
	unsigned int uvIndices[500];
	unsigned int normalIndices[500];
	unsigned int viindex = 0;
	unsigned int uiindex = 0;
	unsigned int niindex = 0;
	
	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("No File??\n");
	}
	//infinite - yess
	while(1)
	{	
		//Only 128??
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break;
		}
		else
		{
			if ( strcmp( lineHeader, "v" ) == 0 )
			{
				hmm_vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.X, &vertex.Y, &vertex.Z );
				temp_vertices[vindex] = vertex;
				vindex++;
			}
			else if ( strcmp( lineHeader, "vt" ) == 0 )
			{
				hmm_vec2 uv;
				fscanf(file, "%f %f\n", &uv.X, &uv.Y );
				temp_uvs[uindex] = uv;
				uindex++;
			}
			else if ( strcmp( lineHeader, "vn" ) == 0 )
			{
				hmm_vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.X, &normal.Y, &normal.Z );
				temp_normals[nindex] = normal;
				//printf("  %i  \n", nindex);
				nindex++;
			}
			else if ( strcmp( lineHeader, "f" ) == 0 )
			{	
				//Indices
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
				if (matches != 9){
					printf("File not read properly\n");
				}
				//Vertex
				vertexIndices[viindex] = vertexIndex[0];
				viindex++;
				vertexIndices[viindex] = vertexIndex[1];
				viindex++;
				vertexIndices[viindex] = vertexIndex[2];
				viindex++;
				//Uv
				uvIndices[uiindex] = uvIndex[0];
				uiindex++;
				uvIndices[uiindex] = uvIndex[1];
				uiindex++;
				uvIndices[uiindex] = uvIndex[2];
				uiindex++;
				//Normals
				normalIndices[niindex] = normalIndex[0];
				niindex++;
				normalIndices[niindex] = normalIndex[0];
				niindex++;
				normalIndices[niindex] = normalIndex[0];
				niindex++;
			}
			else
			{
				// Probably a comment, eat up the rest of the line
				char stupidBuffer[1000];
				fgets(stupidBuffer, 1000, file);
			}
		}
			
	}
	
	//Might destroy pointers ince local?
	model out;
	out.vertices = malloc(sizeof(float) * vindex);
	out.vsize = vindex;
	out.uvs = malloc(sizeof(float) * uindex);
	out.usize = uindex;
	out.normals = malloc(sizeof(float) * nindex);
	out.nsize = nindex;
	
	// For each vertex of each triangle
	for( unsigned int i=0; i<vindex; i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		// Get the attributes thanks to the index
		//-1 because obj starts at 1??
		hmm_vec3 vertex = temp_vertices[ vertexIndex-1 ];
		hmm_vec2 uv = temp_uvs[ uvIndex-1 ];
		hmm_vec3 normal = temp_normals[ normalIndex-1 ];
		
		out.vertices[i] = vertex;
		out.uvs[i] = uv;
		out.normals[i] = normal;
	}

	return out;
}
