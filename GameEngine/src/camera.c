#include "camera.h"

Camera newCamera(hmm_vec3 Position)
{
    Camera camera;
    camera.Pos = HMM_Vec3(0, 0, 0);
    camera.projection = HMM_Perspective(HMM_ToRadians(45), (float)800/(float)600, 0.1f, 500.0f);
    camera.view = HMM_Translate(Position);
    //Testing
    //camera.model = HMM_Rotate(HMM_ToRadians(45), HMM_Vec3(1, 0, 0));
    return camera;
}

void LookAt(Camera* camera, hmm_vec3 target, hmm_vec3 center, hmm_vec3 up)
{
    hmm_mat4 look = HMM_LookAt(target, center, up);
    camera->view = look;
}

hmm_mat4 translateCamera(Camera* camera, hmm_vec3 displacement)
{   
    //Not a translate?
    // HMM_MultiplyMat4ByVec4(camera->view * displacement);
    return HMM_Mat4();
}

void SetCamPos(Camera* camera, hmm_vec3 position)
{
    camera->view = HMM_Translate(position);
}