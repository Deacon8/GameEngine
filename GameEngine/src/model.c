#include "model.h"
#include "memory.h"
#include "HandmadeMath.h"

//FIX MEMORY - linked list??

model LoadOBJ(char* path)
{
	const int i = GetFileSize(path);
	
	
	hmm_vec3 temp_vertices[i];
	unsigned int vindex = 0;
	hmm_vec2 temp_uvs[i];
	unsigned int uindex = 0;
	hmm_vec3 temp_normals[i];
	unsigned int nindex = 0;
	
	unsigned int* vertexIndices, uvIndices, normalIndices;
	unsigned int viindex, uiindex, niindex = 0;
	
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
				nindex++;
			}
			else if ( strcmp( lineHeader, "f" ) == 0 )
			{
				char* vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
				if (matches != 9){
					printf("File can't be read by our simple parser : ( Try exporting with other options\n");
					return false;
				}
				//Convert to pointers
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				vertexIndices[viindex]
				uvIndices    .push_back(uvIndex[0]);
				uvIndices    .push_back(uvIndex[1]);
				uvIndices    .push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
			
	}
}
