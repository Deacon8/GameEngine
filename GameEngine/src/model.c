#include "model.h"
#include "memory.h"
#include "HandmadeMath.h"
#include "glad/glad.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//FIX MEMORY - linked list??

Model LoadOBJ(char* path)
{	
	//printf("Started Loading Model...\n");
	//Using this for size
	const int s = GetFileSize(path);
	
	//Fix Sizes
	hmm_vec3* temp_vertices = malloc(sizeof(hmm_vec3) * s/2);
	unsigned int vindex = 0;
	hmm_vec2* temp_uvs = malloc(sizeof(hmm_vec2) * s/2);
	unsigned int uindex = 0;
	hmm_vec3* temp_normals = malloc(sizeof(hmm_vec3) * s/2);
	unsigned int nindex = 0;
	
	unsigned int* vertexIndices = malloc(sizeof(unsigned int) * s/5);
	unsigned int* uvIndices = malloc(sizeof(unsigned int) * s/5);
	unsigned int* normalIndices = malloc(sizeof(unsigned int) * s/5);
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
		//printf("Loading...");
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
				//printf("VVVV %f , %f , %f\n", vertex.X, vertex.Y, vertex.Z);
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
				// there has to be a better way to do this
				char stupidBuffer[1000];
				fgets(stupidBuffer, 1000, file);
			}
		}
			
	}
	//printf("Done");
	//Nevermind - Move to top - this is stupid

	//Might destroy pointers since local?
	Model out;
	out.vertices = malloc(sizeof(hmm_vec3) * viindex);
	out.vsize = vindex;
	out.vindices = malloc(sizeof(unsigned int) * viindex);
	out.visize = viindex;
	out.uvs = malloc(sizeof(hmm_vec2) * uiindex);
	out.usize = uindex;
	out.uindices = malloc(sizeof(unsigned int) * uiindex);
	out.uisize = uiindex;
	out.normals = malloc(sizeof(hmm_vec3) * niindex);
	out.nsize = nindex;
	out.nindices = malloc(sizeof(unsigned int) * niindex);
	out.nisize = niindex;
	out.all = malloc(sizeof(float) * 8 * out.visize);
	out.allsize = viindex * 8;
	
		// For each vertex of each triangle
	for( unsigned int i = 0; i < viindex; i++)
	{

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		// Get the attributes thanks to the index
		hmm_vec3 vertex = temp_vertices[ vertexIndex-1 ];
		hmm_vec2 uv = temp_uvs[ uvIndex-1 ];
		hmm_vec3 normal = temp_normals[ normalIndex-1 ];
		
		// Put the attributes in buffers
		out.vertices[i] = vertex;
		out.uvs[i] = uv;
		out.normals[i] = normal;
	}
	for(unsigned int i = 0; i < viindex; i++)
	{
		out.vindices[i] = vertexIndices[i];
		//printf("%u\n", out.vindices[i]);
		//printf("%u\n", vertexIndices[i]);
		out.uindices[i] = uvIndices[i];
		out.nindices[i] = normalIndices[i];
	}
	for(int i = 0; i < out.visize; i++)
	{
		out.all[i*8] = out.vertices[i].Elements[0];
		out.all[(i*8)+1] = out.vertices[i].Elements[1];
		out.all[(i*8)+2] = out.vertices[i].Elements[2];
		out.all[(i*8)+3] = out.uvs[i].Elements[0];
		out.all[(i*8)+4] = out.uvs[i].Elements[1];
		out.all[(i*8)+5] = out.normals[i].Elements[0];
		out.all[(i*8)+6] = out.normals[i].Elements[1];
		out.all[(i*8)+7] = out.normals[i].Elements[2];
	}
	fclose(file);

	//Buffers
	unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);
	
    glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, out.allsize*sizeof(float), &out.all[0], GL_STATIC_DRAW);
	out.VAO = VAO;
	//vert
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
	//uv
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
	//normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
	//
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

	free(temp_vertices);
	free(temp_uvs);
	free(temp_normals);
	free(vertexIndices);
	free(uvIndices);
	free(normalIndices);

	return out;
	//printf("Finished Loading Model");
	//remember to triangulate faces in blender
}
