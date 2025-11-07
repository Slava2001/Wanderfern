#include "vec.h"

Vec3d vec3d(GLdouble x, GLdouble y, GLdouble z) {
    return (Vec3d){ .x = x, .y = y, .z = z };
}

Vec3d vec3d_add(Vec3d a, Vec3d b) {
    return vec3d(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3d vec3d_muls(Vec3d a, double scalar) {
    return vec3d(a.x * scalar, a.y * scalar, a.z * scalar);
}
