#include "terrain.h"
#include "util.h"

#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

ResultTerrain terrain_new() {
    Terrain ter;

    ter.texture = try(texture_load("assets/cats.jpg"),
                                   (ResultTerrain)Err(), "Failed to load texture");
                                   ter.sprite_cnt = 120;
    for (unsigned i = 0; i < ter.sprite_cnt; i++) {
        float x = (float)(i % 12);
        float y = (float)(i / 10);
        ter.sprite[i] = try(sprite_new(&ter.texture,
                            rect_new(x / 12.0f, y / 10.0f, 1.0f / 12.0f, 1.0f / 10.0f)),
                            (ResultTerrain)Err(), "Failed to create sprite");
        ter.sprite[i].transform = transform_rotate(&ter.sprite[i].transform,
                                                   (float)M_PI_2, vec3(1, 0, 0));
    }
    return (ResultTerrain)Ok(ter);
}


#define TERRAIN_RADIUS 10
#define CELL_SIDE ((float)(0.5))
GLfloat y_func(GLfloat dist);
GLfloat y_func(GLfloat dist) {
    if (dist < (TERRAIN_RADIUS * CELL_SIDE - CELL_SIDE)) return 0;
    return (TERRAIN_RADIUS * CELL_SIDE - CELL_SIDE) - dist;
}
unsigned hash2d(float x, float y);
unsigned hash2d(float x, float y) {
    unsigned h = (unsigned)((int)x * 374761393 + (int)y * 668265263);
    h = (h ^ (h >> 13)) * 127412617;
    return h ^ (h >> 16);
}

void terrain_draw(Terrain *this,
    const SceneDrawCtx *dctx, const Transform *transform, GLfloat x, GLfloat z
) {
    GLfloat ix = x - TERRAIN_RADIUS * CELL_SIDE - CELL_SIDE / 2.0f;
    ix -= fmodf(ix, CELL_SIDE);
    for (; ix <= x + TERRAIN_RADIUS * CELL_SIDE; ix += CELL_SIDE) {
        GLfloat iz = z - TERRAIN_RADIUS * CELL_SIDE - CELL_SIDE / 2.0f;
        iz -= fmodf(iz, CELL_SIDE);
        for (; iz <= z + TERRAIN_RADIUS * CELL_SIDE; iz += CELL_SIDE) {
            GLfloat dz = iz - z;
            GLfloat dx = ix - x;
            GLfloat dd = sqrtf(dx * dx + dz * dz);
            if (dd < (TERRAIN_RADIUS * CELL_SIDE)) {
                unsigned hash = hash2d(ix / CELL_SIDE, iz / CELL_SIDE);
                Transform t = transform_translate(transform, vec3(ix, y_func(dd), iz));
                t = transform_scale(&t, vec3(CELL_SIDE, 1, CELL_SIDE));
                t = transform_rotate(&t, (float)((hash / 100) % 4) * (float)M_PI_2, vec3(0, 1, 0));
                sprite_draw(&this->sprite[hash % this->sprite_cnt], dctx, &t);
            }
        }
    }
}
