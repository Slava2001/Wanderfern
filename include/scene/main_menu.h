#pragma once

#include "scene.h"
#include "result.h"

typedef struct MainMenu {
    Scene base;
    float angle_rad;
} MainMenu;

decl_result(MainMenu, MainMenu)

ResultMainMenu main_menu_new(void);
