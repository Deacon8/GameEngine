#pragma once

struct Texture
{
    int width, height, nrChannels;
    unsigned char* data;
    
    unsigned int tex;
};typedef struct Texture Texture;

Texture LoadTexture(const char* image);

void SetTexture(Texture texture, unsigned int binding);
