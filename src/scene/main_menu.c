#include "main_menu.h"
#include "gl.h"

#define _USE_MATH_DEFINES
#include <math.h>

int update(void *ctx, const SceneUpdateCtx *uctx);
int draw(void *ctx, const SceneDrawCtx *dctx);
void destroy(void *ctx);

ResultMainMenu main_menu_new(const Window* window) {
    MainMenu main_menu = (MainMenu) {
        .base = (Scene) {
            .update = update,
            .draw = draw,
            .destroy = destroy
        },
        .player = try(playerctl_new((CameraOptions) {
            .position = vec3(-15, 1.5f, 0),
            .angles = vec3(0, 0, 0),
            .fov = 90,
            .aspect_ration = (GLfloat)window->video.width/(GLfloat)window->video.height,
            .near_z = 0.1f,
            .far_z = 1000
        }), (ResultMainMenu)Err(), "Failed to create player"),
        .terrain = try(terrain_new(), (ResultMainMenu)Err(), "Failed to create terrain"),
    };

    main_menu.cat_cube_texture = try(texture_load("assets/cat.jpeg"),
                                   (ResultMainMenu)Err(), "Failed to load texture for cat cube");

    Rect full_texture_rect[6] = { rect_new(0, 0, 1, 1),
                                  rect_new(0, 0, 1, 1),
                                  rect_new(0, 0, 1, 1),
                                  rect_new(0, 0, 1, 1),
                                  rect_new(0, 0, 1, 1),
                                  rect_new(0, 0, 1, 1) };
    main_menu.cat_cube = try(cube_new((const Texture* [6]) { &main_menu.cat_cube_texture,
                                                             &main_menu.cat_cube_texture,
                                                             &main_menu.cat_cube_texture,
                                                             &main_menu.cat_cube_texture,
                                                             &main_menu.cat_cube_texture,
                                                             &main_menu.cat_cube_texture },
                                      full_texture_rect),
                             (ResultMainMenu)Err(), "Failed to create cat cube");
    main_menu.cat_cube.transform = transform_translate(&main_menu.cat_cube.transform,
                                                       vec3(0, 1.5f, 0));
    const char *skybox_face_path[6] = {
        "assets/skybox/pz.jpg",
        "assets/skybox/px.jpg",
        "assets/skybox/nz.jpg",
        "assets/skybox/nx.jpg",
        "assets/skybox/py.jpg",
        "assets/skybox/ny.jpg",
    };
    for (int i = 0; i < 6; i++) {
        main_menu.skybox_textures[i] = try(texture_load(skybox_face_path[i]),
                                           (ResultMainMenu)Err(), "Failed to load skybox face");
    }
    main_menu.skybox = try(cube_new((const Texture* [6]) { &main_menu.skybox_textures[0],
                                                           &main_menu.skybox_textures[1],
                                                           &main_menu.skybox_textures[2],
                                                           &main_menu.skybox_textures[3],
                                                           &main_menu.skybox_textures[4],
                                                           &main_menu.skybox_textures[5] },
                                    full_texture_rect),
                           (ResultMainMenu)Err(), "Failed to crate skybox");
    main_menu.skybox.transform = transform_scale(&main_menu.skybox.transform, vec3(500, 500, 500));
    return (ResultMainMenu) Ok((main_menu));
}

int update(void *ctx, const SceneUpdateCtx *uctx) {
    MainMenu *this = (MainMenu *)ctx;
    playerctl_update(&this->player, uctx);
    this->cat_cube.transform = transform_rotate(&this->cat_cube.transform, 0.01f, vec3(1, 1, 1));
    return 0;
}

int draw(void *ctx, const SceneDrawCtx *dctx) {
    (void)dctx;
    MainMenu *this = (MainMenu *)ctx;
    Transform t = playerctl_get_transform(&this->player);
    Vec3 p = playerctl_get_position(&this->player);
    terrain_draw(&this->terrain, dctx, &t, p.x, p.z);
    cube_draw(&this->cat_cube, dctx, &t);
    cube_draw(&this->skybox, dctx, &t);
    return 0;
}

void destroy(void *ctx) {
    MainMenu *this = (MainMenu *)ctx;
    (void)this;
}
