#pragma once

#include "result.h"
#include "vec.h"
#include "scene.h"
#include "sprite.h"

typedef struct Plant {
    Transform transform;
    Sprite sprite;
    Texture *texture;
} Plant;

decl_result(Plant, Plant);

ResultPlant plant_new(Vec2 pos);
void plant_draw(Plant *this, const SceneDrawCtx *dctx, const Transform *transform);
void plant_drop(Plant *this);
