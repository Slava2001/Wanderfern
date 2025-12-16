#pragma once

#include "mat.h"
#include "vecn.h"

typedef struct Transform {
    Mat4 view;
    Mat4 projection;
} Transform;

Transform transform_new(void);
Transform transform_rotate(const Transform *this, GLfloat angle_rad, Vec3 axis);
Transform transform_translate(const Transform *this, Vec3 shift);
Transform transform_scale(const Transform *this, Vec3 coeff);
Transform transform_apply(const Transform *this, const Transform *oth);
Mat4 transform_get_mvp(const Transform *this, const Transform *model);
Mat4 transform_to_mat(const Transform *this);
Transform transform_view_perspective(const Transform *this,
    float fov, float aspect_ration, float near_z, float far_z
);
Transform transform_view_orthographic(const Transform *this,
    float left, float right,
    float bottom, float top,
    float near_plane, float far_plane
);
Transform transform_view_look_at(const Transform *this, Vec3 pos, Vec3 target, Vec3 up);
Vec3 transform_point(const Transform *this, Vec3 point);
