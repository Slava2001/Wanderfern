#pragma once

#include "gl.h"

typedef struct Vec3 {
    GLfloat x, y, z;
} Vec3;

Vec3 vec3(GLfloat x, GLfloat y, GLfloat z);
Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_muls(Vec3 a, GLfloat scalar);
Vec3 vec3_normalize(Vec3 a);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_neg(Vec3 a);
Vec3 vec3_cross(Vec3 a, Vec3 b);
GLfloat vec3_len(Vec3 a);
GLfloat vec3_dot(Vec3 a, Vec3 b);

typedef struct Vec2 {
    GLfloat x, y;
} Vec2;

Vec2 vec2(GLfloat x, GLfloat y);
Vec2 vec2_add(Vec2 a, Vec2 b);
Vec2 vec2_muls(Vec2 a, GLfloat scalar);
Vec2 vec2_normalize(Vec2 a);
Vec2 vec2_sub(Vec2 a, Vec2 b);
Vec2 vec2_neg(Vec2 a);
Vec2 vec2_rotate(Vec2 a, GLfloat angle_rad);
GLfloat vec2_len(Vec2 a);
