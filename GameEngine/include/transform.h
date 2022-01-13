#pragma once
#include "HandmadeMath.h"

struct Transform
{
    hmm_vec3 position;
    hmm_vec3 rotation;
    hmm_vec3 scale;
    hmm_mat4 final;
};
typedef struct Transform Transform;

void calcTransform(Transform* transform);

Transform CreateNewTransform();
Transform CreateTransform(hmm_vec3 pos, hmm_vec3 rotation, hmm_v3 scale);

void translate(Transform* transform, hmm_vec3 change);
void rotate(Transform* transform, hmm_vec3 change);
void scale(Transform* transform, hmm_vec3 change);