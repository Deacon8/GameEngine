#pragma once

struct Texture
{
    int width, height, nrChannels;
    unsigned char* data;
    
    unsigned int tex;
};typedef struct Texture Texture;

struct Cubemap
{
    int width[6];
    int height[6];
    int nrChannels[6];

    unsigned int* data[6];
    unsigned int tex;
};typedef struct Cubemap Cubemap;
    
Texture LoadTexture(const char* image);

void SetTexture(Texture texture, unsigned int binding);

Texture LoadCubemap(char* name1, char* name2, char* name3, char* name4, char* name5, char* name6);
