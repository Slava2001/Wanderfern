#pragma once

#include "result.h"
#include "gl.h"

typedef struct Texture {
    GLuint texture_id;
} Texture;

decl_result(Texture, Texture);

ResultTexture texture_load(const char *path);
void texture_drop(Texture *this);
