#pragma once

#include "model.h"
#include "shader.h"

struct Renderer
{
    Model model;
    Shader shader;
};
typedef struct Renderer Renderer;