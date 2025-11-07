#pragma once

#include "gl.h"

typedef struct Vec3d {
    GLdouble x, y, z;
} Vec3d;

Vec3d vec3d(GLdouble x, GLdouble y, GLdouble z);
Vec3d vec3d_add(Vec3d a, Vec3d b);
Vec3d vec3d_muls(Vec3d a, double scalar);
