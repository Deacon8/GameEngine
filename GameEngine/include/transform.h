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

enum Direction
{
    Dforward, Dback, Dup, Ddown, Dleft, Dright
};
typedef enum Direction Direction;

void calcTransform(Transform* transform);

Transform CreateNewTransform();
Transform CreateTransform(hmm_vec3 pos, hmm_vec3 rotation, hmm_v3 scale);
hmm_vec3 GetRotation();

void translate(Transform* transform, hmm_vec3 change);
void translateLocal(Transform* transform, Direction, float magnitude);
void rotate(Transform* transform, hmm_vec3 change);
void scale(Transform* transform, hmm_vec3 change);