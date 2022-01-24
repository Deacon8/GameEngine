#include "HandmadeMath.h"
#include "utilities.h"
#include "transform.h"
#include "camera.h"

hmm_vec3 GetRotation(Transform transform)
{
    hmm_vec3 actrot = HMM_Vec3(HMM_CosF(HMM_ToRadians(transform.rotation.X)), HMM_SinF(HMM_ToRadians(transform.rotation.Y)), HMM_SinF(HMM_ToRadians(transform.rotation.Z)));
    return actrot;
}

void calcTransform(Transform* transform)
{
    hmm_mat4 pos = HMM_Translate(transform->position);
    hmm_vec3 actrot = HMM_Vec3(HMM_CosF(HMM_ToRadians(transform->rotation.X)), HMM_SinF(HMM_ToRadians(transform->rotation.Y)), HMM_SinF(HMM_ToRadians(transform->rotation.Z)));
    hmm_mat4 rot = HMM_QuaternionToMat4(EulerToQuat(actrot));
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
    hmm_mat4 final = HMM_MultiplyMat4(HMM_MultiplyMat4(scale, rot), pos);
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

//Currently just forward
void translateLocal(Transform* transform, Direction dir, float magnitude)
{      
    hmm_vec3 front = GetFront(*transform);
    hmm_vec3 up = HMM_Vec3(0, 1, 0);
    hmm_vec3 right = HMM_NormalizeVec3(HMM_Cross(front, up));
    hmm_vec3 upt = HMM_NormalizeVec3(HMM_Cross(front, right));
    upt.X *= magnitude;
    upt.Y *= magnitude;
    upt.Z *= magnitude;
    hmm_vec3 down;
    down.X = -upt.X;
    down.Y = -upt.Y;
    down.Z = upt.Z;
    front.X *= magnitude;
    front.Y *= magnitude;
    front.Z *= magnitude;
    hmm_vec3 back;
    back.X = -front.X;
    back.Y = -front.Y;
    back.Z = -front.Z;
    right.X *= magnitude;
    right.Y *= magnitude;
    right.Z *= magnitude;
    hmm_vec3 left;
    left.X = -right.X;
    left.Y = -right.Y;
    left.Z = -right.Z;

    switch (dir)
    {
    case Dforward:
        transform->position = HMM_AddVec3(transform->position, front);
        break;
    case Dback:
        transform->position = HMM_AddVec3(transform->position, back);
        break;
    case Dright:
        transform->position = HMM_AddVec3(transform->position, right);
        break;
    case Dleft:
        transform->position = HMM_AddVec3(transform->position, left);
        break;
    case Dup:
        transform->position = HMM_AddVec3(transform->position, upt);
        break;
    case Ddown:
        transform->position = HMM_AddVec3(transform->position, down);
        break;
    break;
    }
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