#include "camera.h"
#include "HandmadeMath.h"
#include "utilities.h"

Camera NewCamera()
{
    Camera camera;
    camera.transform = CreateNewTransform();
    camera.projection = HMM_Perspective(HMM_ToRadians(45), (float)800/(float)600, 0.1f, 500.0f);
    camera.view = camera.transform.final;
    return camera;
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

hmm_mat4 GetCameraView(Camera camera)
{
    hmm_mat4 pos = HMM_Translate(camera.transform.position);
    hmm_mat4 rot = HMM_QuaternionToMat4(EulerToQuat(camera.transform.rotation));
    hmm_mat4 view = HMM_MultiplyMat4(rot, pos);
    return view;
}
/*void LookAt(Camera* camera, hmm_vec3 target, hmm_vec3 center, hmm_vec3 up)
{
    hmm_mat4 look = HMM_LookAt(target, center, up);
    camera->view = look;
}*/