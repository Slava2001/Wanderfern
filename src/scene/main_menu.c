#include "main_menu.h"
#include "gl.h"

#define _USE_MATH_DEFINES
#include <math.h>

int update(void *ctx, const SceneUpdateCtx *uctx);
int draw(void *ctx, const SceneDrawCtx *dctx);
void destroy(void *ctx);

ResultMainMenu main_menu_new() {
    Texture texture = try(texture_load("assets/cat.jpeg"),
                          (ResultMainMenu)Err(), "Failed to load texture");
    Sprite sprite = try(sprite_new(&texture, rect_new(0, 0, 1, 1)),
                          (ResultMainMenu)Err(), "Failed to create sprite");
    return (ResultMainMenu) Ok(((MainMenu) {
        .texture = texture,
        .sprite = sprite,
        .base = (Scene) {
            .update = update,
            .draw = draw,
            .destroy = destroy
        },
        .player = try(playerctl_new((CameraOptions) {
            .position = vec3(0, 0, 10),
            .angles = vec3(0, -(float)M_PI_2, 0),
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
    sprite_draw(&this->sprite, dctx, &t);
    return 0;
}

void destroy(void *ctx) {
    MainMenu *this = (MainMenu *)ctx;
    sprite_drop(&this->sprite);
    texture_drop(&this->texture);
}
