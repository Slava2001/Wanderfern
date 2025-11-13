#pragma once

#include "gl.h"

typedef struct Rect {
    GLfloat x;
    GLfloat y;
    GLfloat w;
    GLfloat h;
} Rect;

Rect rect_new(GLfloat x, GLfloat y, GLfloat w, GLfloat h);
