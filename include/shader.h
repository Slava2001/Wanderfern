#pragma once

#include "gl.h"
#include "mat.h"

typedef struct Shader {
    GLuint shader_id;
} Shader;

decl_result(Shader, Shader);

ResultShader shader_new(const char *vertex_src, const char *fragment_src);
void shader_drop(Shader *this);
void shader_use(const Shader *this);
void shader_set_mat4(Shader *this, const char *name, const Mat4 *mat);
