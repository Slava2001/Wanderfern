#pragma once

#include "result.h"
#include "vec.h"
#include "camera.h"
#include "scene.h"

typedef struct PlayerCtl {
    Camera camera;
} PlayerCtl;

decl_result(PlayerCtl, PlayerCtl);

ResultPlayerCtl playerctl_new(CameraOptions ops);
void playerctl_update(PlayerCtl *ctl, const SceneUpdateCtx *uctx);
void playerctl_set_view(PlayerCtl *ctl);
