#include "main_menu.h"
#include "gl.h"

#define _USE_MATH_DEFINES
#include <math.h>

int update(void *ctx, const SceneUpdateCtx *uctx);
int draw(void *ctx);

ResultMainMenu main_menu_new() {
    return (ResultMainMenu) Ok(((MainMenu) {
        .base = (Scene) {
            .update = update,
            .draw = draw,
            .destroy = NULL
        },
        .player = try(playerctl_new((CameraOptions) {
            .position = vec3d(100, 1.5, 100),
            .angles = vec3d(0, 0, 0),
            .fov = 90,
            .aspect = 1,
            .near_z = 0.1,
            .far_z = 100
        }), (ResultMainMenu)Err(), "Failed to create player"),
        .terrain = try(terrain_new(), (ResultMainMenu)Err(), "Failed to create terrain")
    }));
}

int update(void *ctx, const SceneUpdateCtx *uctx) {
    MainMenu *this = (MainMenu *)ctx;
    playerctl_update(&this->player, uctx);
    return 0;
}

void draw_cube(Vec3d pos);

int draw(void *ctx) {
    MainMenu *this = (MainMenu *)ctx;
    Vec3d player_pos = playerctl_get_position(&this->player);
    glPushMatrix();
    playerctl_set_view(&this->player);
    terrain_draw(&this->terrain, player_pos.x, player_pos.z);
    // for (int z = 0; z <= 10; z += 2) {
    //     draw_cube(vec3d(0, 0, z));
    //     draw_cube(vec3d(0, z, 0));
    //     draw_cube(vec3d(z, 0, 0));
    // }
    glPopMatrix();
    return 0;
}

void draw_cube(Vec3d pos) {
    glPushMatrix();
    glTranslated(pos.x, pos.y, pos.z);
    glBegin(GL_TRIANGLE_STRIP);
        struct {
            float r, g, b;
            float x, y, z;
        } array[] = {
            { 1.0f, 0.0f, 0.0f, -0.5f,  0.5f,  0.5f },
            { 0.0f, 1.0f, 0.0f,  0.5f,  0.5f,  0.5f },
            { 0.0f, 0.0f, 1.0f, -0.5f, -0.5f,  0.5f },
            { 0.0f, 1.0f, 1.0f,  0.5f, -0.5f,  0.5f },
            { 1.0f, 1.0f, 0.0f,  0.5f, -0.5f, -0.5f },
            { 0.0f, 1.0f, 0.0f,  0.5f,  0.5f,  0.5f },
            { 1.0f, 0.0f, 1.0f,  0.5f,  0.5f, -0.5f },
            { 1.0f, 0.0f, 0.0f, -0.5f,  0.5f,  0.5f },
            { 1.0f, 1.0f, 1.0f, -0.5f,  0.5f, -0.5f },
            { 0.0f, 1.0f, 1.0f, -0.5f, -0.5f,  0.5f },
            { 0.0f, 1.0f, 0.0f, -0.5f, -0.5f, -0.5f },
            { 1.0f, 1.0f, 0.0f,  0.5f, -0.5f, -0.5f },
            { 1.0f, 1.0f, 1.0f, -0.5f,  0.5f, -0.5f },
            { 1.0f, 0.0f, 1.0f,  0.5f,  0.5f, -0.5f }
        };

        for (unsigned i = 0; i < sizeof(array)/sizeof(struct {
            float r, g, b;
            float x, y, z;
        }); i++) {
            glColor3f(array[i].r, array[i].g, array[i].b);
            glVertex3f(array[i].x, array[i].y, array[i].z);
        }
    glEnd();
    glPopMatrix();
}
