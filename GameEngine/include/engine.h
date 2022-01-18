#pragma once

//forward definitions
struct Entity;
typedef struct Entity Entity;
struct Renderer;
typedef struct Renderer Renderer;
struct Transform;
typedef struct Transform Transform;
struct Texture;
typedef struct Texture Texture;
struct Cubemap;
typedef struct Cubemap Cubemap;

#include "glad/glad.h"
//unnecessary??
//#define GLFW_DLL
#include "glfw/glfw3.h"

#include "HandmadeMath.h"
#include "utilities.h"
#include "stb_image.h"

#include "memory.h"
#include "shader.h"
#include "model.h"
#include "texture.h"

GLFWwindow* window;
#include "loader.h"

#include "transform.h"
#include "camera.h"
#include "renderer.h"
#include "entity.h"

//Add Global Stuff
float deltaTime = 0.0f;
float lastFrame = 0.0f;