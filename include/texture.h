#pragma once

#include "result.h"
#include "gl.h"
#include "mem.h"

typedef struct Texture {
    GLuint texture_id;
} Texture;

decl_result(Texture, Texture*);

ResultTexture texture_load(const char *path);
void texture_use(const Texture *this, GLuint slot_id);
void texture_drop(Texture *this);
