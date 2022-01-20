#include "camera.h"
#include "HandmadeMath.h"
#include "utilities.h"

Camera NewCamera()
{
    Camera camera;
    camera.transform = CreateNewTransform();
<<<<<<< Updated upstream
    camera.projection = HMM_Perspective(HMM_ToRadians(45), (float)800/(float)600, 0.1f, 100.0f);
    camera.view = HMM_LookAt(camera.transform.position, camera.transform.rotation, HMM_Vec3(0, 1, 0));;
=======
    camera.projection = HMM_Perspective(HMM_ToRadians(45), (float)800/(float)600, 0.1f, 500.0f);
    camera.view = camera.transform.final;
    camera.zoom = 45.0f;
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    return camera;
}

Camera CreateCamera(hmm_vec3 position, hmm_vec3 rotation, float fv, float aspect, float near, float far)
{
    Camera camera;
    camera.transform = CreateNewTransform();
    translate(&camera.transform, position);
    camera.projection = HMM_Perspective(HMM_ToRadians(45), aspect, near, far);
<<<<<<< Updated upstream
    camera.view = HMM_LookAt(camera.transform.position, camera.transform.rotation, HMM_Vec3(0, 1, 0));;
=======
    camera.view = camera.transform.final;
    camera.zoom = fv;
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    return camera;
}

hmm_mat4 GetCameraView(Camera camera)
{
    hmm_mat4 pos = HMM_Translate(camera.transform.position);
    hmm_mat4 rot = HMM_QuaternionToMat4(EulerToQuat(camera.transform.rotation));
    hmm_mat4 view = HMM_MultiplyMat4(rot, pos);
    return view;
}

hmm_mat4 GetCameraViewC(Camera camera)
{
    hmm_vec3 front;
	front.X = HMM_CosF(HMM_ToRadians(camera.transform.rotation.Y)) * HMM_CosF(HMM_ToRadians(camera.transform.rotation.X));
	front.Y = HMM_SinF(HMM_ToRadians(camera.transform.rotation.X));
	front.Z = HMM_SinF(HMM_ToRadians(camera.transform.rotation.Y)) * HMM_CosF(HMM_ToRadians(camera.transform.rotation.X));
	front = HMM_NormalizeVec3(front);
	hmm_mat4 view = HMM_LookAt(camera.transform.position, HMM_AddVec3(camera.transform.position, front), HMM_Vec3(0, 1, 0));
    return view;
}
/*void LookAt(Camera* camera, hmm_vec3 target, hmm_vec3 center, hmm_vec3 up)
{
    hmm_mat4 look = HMM_LookAt(target, center, up);
    camera->view = look;
}*/