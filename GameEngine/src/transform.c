#include "HandmadeMath.h"
#include "transform.h"
#include "utilities.h"

void calcTransform(Transform* transform)
{
    hmm_mat4 pos = HMM_Translate(transform->position);
    hmm_mat4 rot = HMM_QuaternionToMat4(EulerToQuat(transform->rotation));
    hmm_mat4 scale = HMM_Scale(transform->scale);
    hmm_mat4 final = HMM_MultiplyMat4(pos, HMM_MultiplyMat4(rot, scale));
    transform->final = final;
}

Transform CreateNewTransform()
{   
    Transform transform;
    transform.position = HMM_Vec3(0, 0, 0);
    transform.rotation = HMM_Vec3(0, 0, 0);
    transform.scale = HMM_Vec3(1, 1, 1);
    hmm_mat4 pos = HMM_Translate(transform.position);
    hmm_mat4 rot = HMM_QuaternionToMat4(EulerToQuat(transform.rotation));
    hmm_mat4 scale = HMM_Scale(transform.scale);
    hmm_mat4 final = HMM_MultiplyMat4(pos, HMM_MultiplyMat4(rot, scale));
    transform.final = final;
    return transform;
}

Transform CreateTransform(hmm_vec3 pos, hmm_vec3 rot, hmm_v3 scale)
{   
    Transform transform;
    transform.position = pos;
    transform.rotation = rot;
    transform.scale = scale;
    calcTransform(&transform);
    return transform;
}

void translate(Transform* transform, hmm_vec3 change)
{
    transform->position = HMM_AddVec3(transform->position, change);
    calcTransform(transform);
}

void rotate(Transform* transform, hmm_vec3 change)
{
    transform->rotation = HMM_AddVec3(transform->rotation, change);
    calcTransform(transform);
}

void scale(Transform* transform, hmm_vec3 change)
{
    transform->scale = HMM_AddVec3(transform->scale, change);
    calcTransform(transform);
}