#pragma once
#include "HandmadeMath.h"
#include "transform.h"

struct Camera
{
    Transform transform;
    hmm_mat4 view;
    hmm_mat4 projection;
    float zoom;
    /*float fv;
    float aspect;
    float near;
    float far;*/
};typedef struct Camera Camera;

Camera NewCamera();
Camera CreateCamera(hmm_vec3 position, hmm_vec3 rotation, float fv, float aspect, float near, float far);

hmm_mat4 GetCameraView(Camera camera);
hmm_mat4 GetCameraViewC(Camera camera);
//void CalcView(Camera* camera);

//void LookAt(Camera* camera, hmm_vec3 target, hmm_vec3 center, hmm_vec3 up);