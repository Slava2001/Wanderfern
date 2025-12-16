#pragma once

#include "result.h"
#include "vecn.h"
#include "scene.h"
#include "sprite.h"
#include <stddef.h>

typedef struct PlantEdge {
    GLfloat start_radius;
    Vec3 start_color;
    GLfloat end_radius;
    Vec3 end_color;
    GLfloat len;
    size_t next_cnt;
    struct PlantEdge *next;
} PlantEdge;

typedef struct Plant {
    Transform transform;
    GLuint vertex_arrays;
    GLuint vertex_buff;
    GLuint index_buff;
    GLsizei index_cnt;
    Shader *shader;
} Plant;

decl_result(Plant, Plant);

ResultPlant plant_new(Vec2 pos);
void plant_draw(Plant *this, const SceneDrawCtx *dctx, const Transform *transform);
void plant_drop(Plant *this);
