#include "camera.h"

Camera newCamera(hmm_vec3 Position)
{
    Camera camera;
    camera.Pos = HMM_Vec3(0, 0, 0);
    camera.projection = HMM_Perspective(HMM_ToRadians(45), (float)800/(float)600, 0.1f, 100.0f);
    camera.view = HMM_Translate(Position);
    //Testing
    //camera.model = HMM_Rotate(HMM_ToRadians(45), HMM_Vec3(1, 0, 0));
    return camera;
}

void LookAt(Camera* camera, hmm_vec3 target, hmm_vec3 center, hmm_vec3 up)
{
    hmm_mat4 look = HMM_LookAt(target, center, up);
}

hmm_mat4 translateCamera(Camera* camera, hmm_vec3 displacement)
{   
    //Not a translate
    return HMM_Translate(HMM_AddVec3(camera->Pos, displacement));
}