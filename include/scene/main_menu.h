#pragma once

#include "scene.h"
#include "result.h"
#include "player_ctl.h"
#include "terrain.h"
#include "sprite.h"
#include "texture.h"
#include "cube.h"

typedef struct MainMenu {
    Scene base;
    PlayerCtl player;
    Terrain terrain;
    Texture cat_cube_texture;
    Cube cat_cube;
    Texture skybox_textures[6];
    Cube skybox;
} MainMenu;

decl_result(MainMenu, MainMenu);

ResultMainMenu main_menu_new(const Window* windows);
