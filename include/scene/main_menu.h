#pragma once

#include "scene.h"

typedef struct MainMenu {
    Scene base;
    float angle_rad;
} MainMenu;

int main_menu_new(MainMenu *main_menu);
