#include "texture.h"
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"
#include "shader.h"
#include "camera.h"
#include <string.h>

const static float skyboxVertices[] = 
{
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
};	

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
const static float skyboxVertices[] = 
{
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

<<<<<<< Updated upstream
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};	

=======
>>>>>>> Stashed changes
Texture LoadCubemap(Shader shader, char* name1, char* name2, char* name3, char* name4, char* name5, char* name6)
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
    //This is dumb but whatever
    cubemap.data = stbi_load(name1, &cubemap.width, &cubemap.height, &cubemap.nrChannels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 0, 0, GL_RGB, cubemap.width, cubemap.height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubemap.data);
    stbi_image_free(cubemap.data);
    cubemap.data = stbi_load(name2, &cubemap.width, &cubemap.height, &cubemap.nrChannels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1, 0, GL_RGB, cubemap.width, cubemap.height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubemap.data);
    stbi_image_free(cubemap.data);
    cubemap.data = stbi_load(name3, &cubemap.width, &cubemap.height, &cubemap.nrChannels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 2, 0, GL_RGB, cubemap.width, cubemap.height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubemap.data);
    stbi_image_free(cubemap.data);
    cubemap.data = stbi_load(name4, &cubemap.width, &cubemap.height, &cubemap.nrChannels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 3, 0, GL_RGB, cubemap.width, cubemap.height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubemap.data);
    stbi_image_free(cubemap.data);
    cubemap.data = stbi_load(name5, &cubemap.width, &cubemap.height, &cubemap.nrChannels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 4, 0, GL_RGB, cubemap.width, cubemap.height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubemap.data);
    stbi_image_free(cubemap.data);
    cubemap.data = stbi_load(name6, &cubemap.width, &cubemap.height, &cubemap.nrChannels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 5, 0, GL_RGB, cubemap.width, cubemap.height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubemap.data);
    stbi_image_free(cubemap.data);
    //printf("t: %i\n", glGetError());
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glUseProgram(shader.ShaderProgram);
	SetUniformSampler2D(shader, "skybox", 0);
    cubemap.VAO = skyboxVAO;
    return cubemap;
}

void DrawCubemap(Texture texture, Shader shader, Camera camera)
{
    glDepthMask(GL_FALSE);  // change depth function so depth test passes when values are equal to depth buffer's content
    glUseProgram(shader.ShaderProgram);
<<<<<<< Updated upstream
    hmm_mat4 view = HMM_LookAt(camera.transform.position, camera.transform.rotation, HMM_Vec3(0, 1, 0)); // remove translation from the view matrix
    //hmm_mat4 view = HMM_LookAt(camera.transform.position, GetRotation(camera.transform), HMM_Vec3(0, 1, 0)); // remove translation from the view matrix
    
    view.Elements[3][0] = 0;
    view.Elements[3][1] = 0;
    view.Elements[3][2] = 0;
=======
    hmm_mat4 view = GetCameraViewC(camera);
    view.Elements[3][0] = 0;
    view.Elements[3][1] = 0;
    view.Elements[3][2] = 0;
    view.Elements[0][3] = 0;
    view.Elements[0][3] = 0;
    view.Elements[0][3] = 0;
>>>>>>> Stashed changes
    SetUniformMat4(shader, "view", view);
    SetUniformMat4(shader, "projection", camera.projection);
    // skybox cube
    glBindVertexArray(texture.VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture.tex);
    //printf("wf; %i", cubemap.tex);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
}