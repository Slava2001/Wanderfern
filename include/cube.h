#pragma once

#include "gl.h"
#include "result.h"
#include "scene.h"
#include "shader.h"
#include "transform.h"
#include "texture.h"
#include "rect.h"
#include "sprite.h"

typedef struct Cube {
    Transform transform;
    Sprite face[6];
} Cube;

decl_result(Cube, Cube);

ResultCube cube_new(const Texture *textures[], Rect rects[]);
void cube_draw(Cube *this, const SceneDrawCtx *dctx, const Transform *transform);
void cube_drop(Cube *this);
