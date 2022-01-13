#pragma once
#include "transform.h"
#include "renderer.h"

struct Entity
{   
    //Change to pointer + have check for component
    Transform transform;
    Renderer renderer;
};
typedef struct Entity Entity;
