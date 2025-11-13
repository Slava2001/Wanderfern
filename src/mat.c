#include "mat.h"

Mat4 mat4_new_from_value(GLfloat val) {
    return (Mat4) {
        .values = { val, val, val, val,
                    val, val, val, val,
                    val, val, val, val,
                    val, val, val, val }
    };
}

Mat4 mat4_new_identity() {
    return (Mat4) {
        .values = { 1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f }
    };
}

Mat4 mat4_mul(const Mat4 *a, const Mat4 *b) {
    Mat4 result;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            result.values[row * 4 + col] =
                a->values[0 * 4 + col] * b->values[row * 4 + 0] +
                a->values[1 * 4 + col] * b->values[row * 4 + 1] +
                a->values[2 * 4 + col] * b->values[row * 4 + 2] +
                a->values[3 * 4 + col] * b->values[row * 4 + 3];
        }
    }
    return result;
}

Mat4 mat4_new_from_array(GLfloat val[static 16]) {
    Mat4 res;
    for (int i = 0; i < 16; i++) {
        res.values[i] = val[i];
    }
    return res;
}
