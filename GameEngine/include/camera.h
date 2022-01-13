#pragma once
#include "HandmadeMath.h"
#include "transform.h"

struct Camera
{
    Transform transform;
    hmm_mat4 view;
    hmm_mat4 projection;
};typedef struct Camera Camera;

Camera NewCamera();
Camera CreateCamera(hmm_vec3 position, hmm_vec3 rotation, float fv, float aspect, float near, float far);

//void LookAt(Camera* camera, hmm_vec3 target, hmm_vec3 center, hmm_vec3 up);