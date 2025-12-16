#pragma once

#include "gl.h"
#include "vecn.h"

typedef struct Mat4 {
    GLfloat values[16]; // This field must be first (used for cast).
} Mat4;

Mat4 mat4_new_from_value(GLfloat val);
Mat4 mat4_new_from_array(GLfloat val[static 16]);
Mat4 mat4_new_identity(void);
Mat4 mat4_mul(const Mat4 *a, const Mat4 *b);
Vec3 mat4_mulv(const Mat4* this, Vec3 point);
