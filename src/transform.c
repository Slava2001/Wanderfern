#include "transform.h"
#define _USE_MATH_DEFINES
#include <math.h>

Transform transform_new() {
    return (Transform) {
        .view = mat4_new_identity(),
        .projection = mat4_new_identity()
    };
}

Transform transform_rotate(const Transform *this, GLfloat angle_rad, Vec3 axis) {
    Vec3 axis_norm = vec3_normalize(axis);
    float x = axis_norm.x;
    float y = axis_norm.y;
    float z = axis_norm.z;
    float sa = sinf(angle_rad);
    float ca = cosf(angle_rad);
    Mat4 rotate_mat = mat4_new_from_array(
        (GLfloat[16]) {
          ca+x*x*(1-ca),   y*x*(1-ca)+z*sa, z*x*(1-ca)-y*sa, 0.0f,
          x*y*(1-ca)-z*sa, ca+y*y*(1-ca),   z*y*(1-ca)+x*sa, 0.0f,
          x*z*(1-ca)+y*sa, y*z*(1-ca)-x*sa, ca+z*z*(1-ca),   0.0f,
          0.0f,            0.0f,            0.0f,            1.0f,
        }
    );
    return (Transform) {
        .projection = this->projection,
        .view = mat4_mul(&this->view, &rotate_mat)
    };
}

Transform transform_translate(const Transform *this, Vec3 shift) {
    Mat4 shift_mat = mat4_new_identity();
    shift_mat.values[12] = shift.x;
    shift_mat.values[13] = shift.y;
    shift_mat.values[14] = shift.z;
    return (Transform) {
        .projection = this->projection,
        .view = mat4_mul(&this->view, &shift_mat)
    };
}

Transform transform_scale(const Transform *this, Vec3 coeff) {
    Mat4 scale = mat4_new_identity();
    scale.values[0] = coeff.x;
    scale.values[5] = coeff.y;
    scale.values[10] = coeff.z;
    scale.values[15] = 1.0f;
    return (Transform) {
        .projection = this->projection,
        .view = mat4_mul(&this->view, &scale)
    };
}

Transform transform_apply(const Transform *this, const Transform *oth) {
    return (Transform) {
        .projection = this->projection,
        .view = mat4_mul(&this->view, &oth->view)
    };
}

Mat4 transform_get_mvp(const Transform *this, const Transform *model) {
    Mat4 pv = mat4_mul(&this->projection, &this->view);
    return mat4_mul(&pv, &model->view);
}

Mat4 transform_to_mat(const Transform *this) {
    return mat4_mul(&this->projection, &this->view);
}

Vec3 transform_point(const Transform *this, Vec3 point) {
    Mat4 pv = transform_to_mat(this);
    return mat4_mulv(&pv, point);
}

Transform transform_view_look_at(const Transform *this, Vec3 pos, Vec3 target, Vec3 up) {
    Vec3 dir = vec3_normalize(vec3_sub(target, pos));
    Vec3 right = vec3_normalize(vec3_cross(dir, up));
    Vec3 cam_up = vec3_cross(right, dir);
    dir = vec3_neg(dir);
    float dot_x = -vec3_dot(right, pos);
    float dot_y = -vec3_dot(cam_up, pos);
    float dot_z = -vec3_dot(dir, pos);
    Mat4 loot_at = mat4_new_from_array((GLfloat[16]){
        right.x, cam_up.x, dir.x, 0.0f,
        right.y, cam_up.y, dir.y, 0.0f,
        right.z, cam_up.z, dir.z, 0.0f,
        dot_x,   dot_y,    dot_z, 1.0f
    });
    return (Transform) {
        .projection = loot_at,
        .view = this->projection
    };
}

Transform transform_view_perspective(const Transform *this,
    float fov, float aspect_ration, float near_z, float far_z
) {
    float top = near_z * tanf(((float)M_PI / 180.0f) * (fov * 0.5f));
    float bottom = -top;
    float right = top * aspect_ration;
    float left = -right;
    GLfloat arr[16] = { 0.0f };
    arr[0]  = (2.0f * near_z) / (right - left);
    arr[5]  = (2.0f * near_z) / (top - bottom);
    arr[8]  = (right + left) / (right - left);
    arr[9]  = (top + bottom) / (top - bottom);
    arr[10] = -((far_z + near_z) / (far_z - near_z));
    arr[11] = -1.0f;
    arr[14] = -((2.0f * far_z * near_z) / (far_z - near_z));
    Mat4 view = mat4_new_from_array(arr);
    return (Transform) {
        .projection = view,
        .view = this->projection
    };
}

Transform transform_view_orthographic(const Transform *this,
    float left, float right,
    float bottom, float top,
    float near_plane, float far_plane
) {
    GLfloat arr[16] = { 0.0f };
    arr[0]  = 2.0f / (right - left);
    arr[5]  = 2.0f / (top - bottom);
    arr[10] = -2.0f / (far_plane - near_plane);
    arr[12] = -(right + left) / (right - left);
    arr[13] = -(top + bottom) / (top - bottom);
    arr[14] = -(far_plane + near_plane) / (far_plane - near_plane);
    arr[15] = 1.0f;
    Mat4 view = mat4_new_from_array(arr);
    return (Transform) {
        .projection = view,
        .view = this->projection
    };
}
