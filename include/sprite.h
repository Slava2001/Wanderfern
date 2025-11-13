#pragma once

#include "gl.h"
#include "result.h"
#include "scene.h"
#include "shader.h"
#include "transform.h"
#include "texture.h"
#include "rect.h"

typedef struct Sprite {
    Transform transform;
    const Texture *texture;
    Shader *shader;
    GLuint vertex_buff;
    GLuint vertex_arrays;
    GLuint index_buff;
} Sprite;

decl_result(Sprite, Sprite);

ResultSprite sprite_new(const Texture *texture, Rect rect);
void sprite_draw(Sprite *this, const SceneDrawCtx *dctx, const Transform *transform);
void sprite_drop(Sprite *this);
