#include "rect.h"

Rect rect_new(GLfloat x, GLfloat y, GLfloat w, GLfloat h) {
    return (Rect) {
        .x = x,
        .y = y,
        .w = w,
        .h = h
    };
}
