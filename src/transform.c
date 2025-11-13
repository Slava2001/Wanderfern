#include "transform.h"
#include "math.h"

Transform transform_new() {
    return (Transform) {
        .mat = mat4_new_identity()
    };
}

Transform transform_rotate(const Transform *this, GLfloat angle_rad, Vec3d axis) {
    Vec3d axis_norm = vec3d_normalize(axis);
    float x = (float)axis_norm.x;
    float y = (float)axis_norm.y;
    float z = (float)axis_norm.z;
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
        .mat = mat4_mul(&this->mat, &rotate_mat)
    };
}

Transform transform_translate(const Transform *this, Vec3d shift) {
    Mat4 shift_mat = mat4_new_identity();
    shift_mat.values[12] = (float)shift.x;
    shift_mat.values[13] = (float)shift.y;
    shift_mat.values[14] = (float)shift.z;
    return (Transform) {
        .mat = mat4_mul(&this->mat, &shift_mat)
    };
}

Transform transform_scale(const Transform *this, Vec3d coeff) {
    Mat4 scale = mat4_new_identity();
    scale.values[0] = (float)coeff.x;
    scale.values[5] = (float)coeff.y;
    scale.values[10] = (float)coeff.z;
    scale.values[15] = 1.0f;
    return (Transform) {
        .mat = mat4_mul(&this->mat, &scale)
    };
}

Transform transform_mul(const Transform *this, const Transform *oth) {
    return (Transform) {
        .mat = mat4_mul(&this->mat, &oth->mat)
    };
}

const Mat4* transform_get_mat4(const Transform *this) {
    return &this->mat;
}
