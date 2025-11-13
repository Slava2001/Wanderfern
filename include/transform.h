#pragma once

#include "mat.h"
#include "vec.h"

typedef struct Transform {
    Mat4 mat;
} Transform;

Transform transform_new(void);
Transform transform_rotate(const Transform *this, GLfloat angle_rad, Vec3d axis);
Transform transform_translate(const Transform *this, Vec3d shift);
Transform transform_scale(const Transform *this, Vec3d coeff);
Transform transform_mul(const Transform *this, const Transform *oth);
const Mat4* transform_get_mat4(const Transform *this);
