#pragma once
#include "HandmadeMath.h"

struct Camera
{
    hmm_vec3 Pos;
    hmm_mat4 model;
    hmm_mat4 view;
    hmm_mat4 projection;
};typedef struct Camera Camera;

Camera newCamera(hmm_vec3 Position);

void LookAt(Camera* camera, hmm_vec3 target, hmm_vec3 center, hmm_vec3 up);

hmm_mat4 translateCamera(Camera* camera, hmm_vec3 displacement);