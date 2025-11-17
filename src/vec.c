#include "vec.h"
#include <math.h>

Vec3 vec3(GLfloat x, GLfloat y, GLfloat z) {
    return (Vec3){ .x = x, .y = y, .z = z };
}

Vec3 vec3_add(Vec3 a, Vec3 b) {
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 vec3_sub(Vec3 a, Vec3 b) {
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 vec3_neg(Vec3 a) {
    return vec3(-a.x, -a.y, -a.z);
}

Vec3 vec3_muls(Vec3 a, GLfloat scalar) {
    return vec3(a.x * scalar, a.y * scalar, a.z * scalar);
}

GLfloat vec3_len(Vec3 a) {
    return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

Vec3 vec3_normalize(Vec3 a) {
    return vec3_muls(a, 1.0f / vec3_len(a));
}

Vec3 vec3_cross(Vec3 a, Vec3 b) {
    return vec3((a.y * b.z) - (a.z * b.y),
                (a.z * b.x) - (a.x * b.z),
                (a.x * b.y) - (a.y * b.x));
}

GLfloat vec3_dot(Vec3 a, Vec3 b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vec2 vec2(GLfloat x, GLfloat y) {
    return (Vec2){ .x = x, .y = y };
}

Vec2 vec2_add(Vec2 a, Vec2 b) {
    return vec2(a.x + b.x, a.y + b.y);
}

Vec2 vec2_sub(Vec2 a, Vec2 b) {
    return vec2(a.x - b.x, a.y - b.y);
}

Vec2 vec2_neg(Vec2 a) {
    return vec2(-a.x, -a.y);
}

Vec2 vec2_muls(Vec2 a, GLfloat scalar) {
    return vec2(a.x * scalar, a.y * scalar);
}

GLfloat vec2_len(Vec2 a) {
    return sqrtf(a.x * a.x + a.y * a.y);
}

Vec2 vec2_normalize(Vec2 a) {
    return vec2_muls(a, 1.0f / vec2_len(a));
}

Vec2 vec2_rotate(Vec2 a, GLfloat angle_rad) {
    return vec2(a.x * cosf(angle_rad) - a.y * sinf(angle_rad),
                a.x * sinf(angle_rad) + a.y * cosf(angle_rad));
}
