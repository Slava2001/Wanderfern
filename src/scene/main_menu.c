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
    glPopMatrix();
    return 0;
}
