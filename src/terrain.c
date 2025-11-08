#include "terrain.h"
#include "util.h"

#include <stdlib.h>
#include <math.h>

ResultTerrain terrain_new() {
    return (ResultTerrain)Ok((Terrain) {});
}

#define TERRAIN_RADIUS 20
#define CELL_SIDE 0.5
void terrain_draw(Terrain *ter, GLdouble x, GLdouble z) {
    (void)ter;
    GLdouble ix = (x - TERRAIN_RADIUS * CELL_SIDE);
    ix -= fmod(ix, CELL_SIDE);
    GLdouble iz = (z - TERRAIN_RADIUS * CELL_SIDE);
    iz -= fmod(iz, CELL_SIDE);
    glPushMatrix();
    glTranslatef((GLfloat)ix, 0, (GLfloat)iz);
    for (int iix = 0; iix < 2 * TERRAIN_RADIUS; iix++) {
        glPushMatrix();
        for (int iiz = 0; iiz < 2 * TERRAIN_RADIUS; iiz++) {
            GLdouble dx = x - ix - iix * CELL_SIDE;
            GLdouble dz = z - iz - iiz * CELL_SIDE;
            GLdouble dd = sqrt(dx * dx + dz * dz) / (TERRAIN_RADIUS * CELL_SIDE);
            if (dd < 1.0) {
                GLdouble y = 3 + -10 * sin(dd);
                y = CLAMP(y, -10, 0);
                glBegin(GL_QUADS);
                    glColor3d(0.5 + 0.5 * ((float)(((int)(ix / CELL_SIDE) + iix) % 2)),
                              0.5 + 0.5 * ((float)(((int)(iz / CELL_SIDE) + iiz) % 2)),
                              0.5);
                    glVertex3d(-CELL_SIDE / 2, y, -CELL_SIDE / 2);
                    glVertex3d( CELL_SIDE / 2, y, -CELL_SIDE / 2);
                    glVertex3d( CELL_SIDE / 2, y,  CELL_SIDE / 2);
                    glVertex3d(-CELL_SIDE / 2, y,  CELL_SIDE / 2);
                glEnd();
            }
            glTranslatef(0, 0, CELL_SIDE);
        }
        glPopMatrix();
        glTranslatef(CELL_SIDE, 0, 0);
    }
    glPopMatrix();
}
