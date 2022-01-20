#pragma once
struct Shader;
typedef struct Shader Shader;
struct Camera;
typedef struct Camera Camera;

struct Texture
{
    int width, height, nrChannels;
    unsigned char* data;
    
    unsigned int tex;

<<<<<<< Updated upstream
<<<<<<< Updated upstream
    //for cubemaps temp
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    unsigned int VAO;
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

<<<<<<< Updated upstream
<<<<<<< Updated upstream
Texture LoadCubemap(Shader shader, char* name1, char* name2, char* name3, char* name4, char* name5, char* name6);
=======
=======
>>>>>>> Stashed changes
struct Shader;
typedef struct Shader Shader;
struct Camera;
typedef struct Camera Camera;
Texture LoadCubemap(Shader shader, char* name1, char* name2, char* name3, char* name4, char* name5, char* name6);

<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
void DrawCubemap(Texture texture, Shader shader, Camera camera);