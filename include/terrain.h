#pragma once

#include "result.h"
#include "gl.h"

typedef struct Terrain {
} Terrain;

decl_result(Terrain, Terrain);

ResultTerrain terrain_new(void);
void terrain_draw(Terrain *this, GLdouble x, GLdouble z);
