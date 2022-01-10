#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"

Texture LoadTexture(const char* image)
{
    Texture local;
    local.data = stbi_load(image, &local.width, &local.height, &local.nrChannels, 0); 
    //free memory?
    if(!local.data){printf("Texture Failed to Load");}

    //Nevermind - Basic Parameters - Maybe dont assign each time lol


    unsigned int texture;
    glGenTextures(1, &texture); 
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, local.width, local.height, 0, GL_RGB, GL_UNSIGNED_BYTE, local.data);
    glGenerateMipmap(GL_TEXTURE_2D);

    local.tex = texture;
    //Add to glsl

    return local;
}

void SetTexture(Texture texture, unsigned int binding)
{
    glActiveTexture(GL_TEXTURE0 + binding);
    glBindTexture(GL_TEXTURE_2D, texture.tex);
}