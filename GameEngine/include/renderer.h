#pragma once

#include "model.h"
#include "shader.h"
struct Entity;
typedef struct Entity Entity;
#include "texture.h"

enum ShaderType
{
    basic_color, 
    basic_texture,
    basic_time
};
typedef enum ShaderType ShaderType;

struct Renderer
{
    Model model;
    Shader shader;

    ShaderType shadertype;
    //Change - Inefficient?
    Texture texture;
    hmm_vec3 color;
};
typedef struct Renderer Renderer;

#include "entity.h"

void PreDraw();
void PostDraw();

void DrawEntity(Entity entity, Camera camera);