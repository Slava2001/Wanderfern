#pragma once

#include "result.h"
#include "vec.h"
#include "scene.h"
#include "sprite.h"
#include <stddef.h>

typedef struct PlantNode {
    Transform transform;
    GLfloat start_radius;
    Vec3 start_color;
    GLfloat end_radius;
    Vec3 end_color;
    GLfloat len;
    size_t next_cnt;
    struct PlantNode *next;
} PlantNode;

typedef struct Plant {
    Transform transform;
    PlantNode buff[100];
    Shader *shader;
    GLuint vertex_buff;
    GLuint vertex_arrays;
    GLuint index_buff;
    GLsizei index_cnt;
} Plant;

decl_result(Plant, Plant);

ResultPlant plant_new(Vec2 pos);
void plant_draw(Plant *this, const SceneDrawCtx *dctx, const Transform *transform);
void plant_drop(Plant *this);
