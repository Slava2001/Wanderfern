#pragma once

#include "result.h"
#include "texture.h"
#include "sprite.h"
#include "gl.h"
#include "scene.h"
#include "transform.h"

typedef struct Terrain {
    Texture texture;
    Sprite sprite[120];
    unsigned sprite_cnt;
} Terrain;

decl_result(Terrain, Terrain);

ResultTerrain terrain_new(void);
void terrain_draw(Terrain *this,
    const SceneDrawCtx *dctx, const Transform *transform, GLfloat x, GLfloat z
);
