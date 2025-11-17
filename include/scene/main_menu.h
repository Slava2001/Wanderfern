#pragma once

#include "scene.h"
#include "result.h"
#include "player_ctl.h"
#include "terrain.h"
#include "sprite.h"
#include "texture.h"

typedef struct MainMenu {
    Scene base;
    PlayerCtl player;
    Terrain terrain;
} MainMenu;

decl_result(MainMenu, MainMenu);

ResultMainMenu main_menu_new(void);
