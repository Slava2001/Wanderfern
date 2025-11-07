#pragma once

#include "scene.h"
#include "result.h"
#include "player_ctl.h"

typedef struct MainMenu {
    Scene base;
    PlayerCtl player;
} MainMenu;

decl_result(MainMenu, MainMenu);

ResultMainMenu main_menu_new(void);
