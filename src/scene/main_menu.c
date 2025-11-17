#include "main_menu.h"
#include "gl.h"

#define _USE_MATH_DEFINES
#include <math.h>

int update(void *ctx, const SceneUpdateCtx *uctx);
int draw(void *ctx, const SceneDrawCtx *dctx);
void destroy(void *ctx);

ResultMainMenu main_menu_new() {
    return (ResultMainMenu) Ok(((MainMenu) {
        .base = (Scene) {
            .update = update,
            .draw = draw,
            .destroy = destroy
        },
        .player = try(playerctl_new((CameraOptions) {
            .position = vec3(0, 1.5f, 0),
            .angles = vec3(-1.5, 0, 0),
            .fov = 90,
            .aspect_ration = 1,
            .near_z = 0.1f,
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

int draw(void *ctx, const SceneDrawCtx *dctx) {
    (void)dctx;
    MainMenu *this = (MainMenu *)ctx;
    Transform t = playerctl_get_transform(&this->player);
    Vec3 p = playerctl_get_position(&this->player);
    terrain_draw(&this->terrain, dctx, &t, p.x, p.z);
    return 0;
}

void destroy(void *ctx) {
    MainMenu *this = (MainMenu *)ctx;
    (void)this;
}
