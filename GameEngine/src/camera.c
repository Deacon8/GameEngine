#include "camera.h"
#include "HandmadeMath.h"

Camera NewCamera()
{
    Camera camera;
    camera.transform = CreateNewTransform();
    camera.projection = HMM_Perspective(HMM_ToRadians(45), (float)800/(float)600, 0.1f, 500.0f);
    camera.view = camera.transform.final;
}

Camera CreateCamera(hmm_vec3 position, hmm_vec3 rotation, float fv, float aspect, float near, float far)
{
    Camera camera;
    camera.transform = CreateNewTransform();
    translate(&camera.transform, position);
    camera.projection = HMM_Perspective(HMM_ToRadians(45), aspect, near, far);
    camera.view = camera.transform.final;
    return camera;
}

/*void LookAt(Camera* camera, hmm_vec3 target, hmm_vec3 center, hmm_vec3 up)
{
    hmm_mat4 look = HMM_LookAt(target, center, up);
    camera->view = look;
}*/