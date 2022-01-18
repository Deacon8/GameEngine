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

Texture LoadCubemap(char* path, char* name1, char* name2, char* name3, char* name4, char* name5, char* name6)
{
    Texture cubemap;
    glGenTextures(1, &cubemap.tex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap.tex);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    //using actual texture class kinda pointless but whatever
    //also no error checking lol
    // loads a cubemap texture from 6 individual texture faces
    // order:
    // +X (right)
    // -X (left)
    // +Y (top)
    // -Y (bottom)
    // +Z (front) 
    // -Z (back)

    cubemap.data = stbi_load(strcat(path, name1), &cubemap.width, &cubemap.height, &cubemap.nrChannels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 0, 0, GL_RGB, cubemap.width, cubemap.height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubemap.data);
    stbi_image_free(cubemap.data);
    cubemap.data = stbi_load(strcat(path, name2), &cubemap.width, &cubemap.height, &cubemap.nrChannels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1, 0, GL_RGB, cubemap.width, cubemap.height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubemap.data);
    stbi_image_free(cubemap.data);
    cubemap.data = stbi_load(strcat(path, name3), &cubemap.width, &cubemap.height, &cubemap.nrChannels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 2, 0, GL_RGB, cubemap.width, cubemap.height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubemap.data);
    stbi_image_free(cubemap.data);
    cubemap.data = stbi_load(strcat(path, name4), &cubemap.width, &cubemap.height, &cubemap.nrChannels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 3, 0, GL_RGB, cubemap.width, cubemap.height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubemap.data);
    stbi_image_free(cubemap.data);
    cubemap.data = stbi_load(strcat(path, name5), &cubemap.width, &cubemap.height, &cubemap.nrChannels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 4, 0, GL_RGB, cubemap.width, cubemap.height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubemap.data);
    stbi_image_free(cubemap.data);
    cubemap.data = stbi_load(strcat(path, name6), &cubemap.width, &cubemap.height, &cubemap.nrChannels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 5, 0, GL_RGB, cubemap.width, cubemap.height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubemap.data);
    stbi_image_free(cubemap.data);

    return cubemap;
}