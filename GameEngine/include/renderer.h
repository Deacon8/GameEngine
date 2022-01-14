#pragma once

#include "model.h"
#include "shader.h"

struct Renderer
{
    Model model;
    Shader shader;
    short hastexture;
    Texture texture;
};
typedef struct Renderer Renderer;

#include "entity.h"

void PreDraw();
void PostDraw();

void DrawEntity(Entity entity, Camera camera);