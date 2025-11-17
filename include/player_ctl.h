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
void playerctl_update(PlayerCtl *this, const SceneUpdateCtx *uctx);
Transform playerctl_get_transform(PlayerCtl *this);
Vec3 playerctl_get_position(PlayerCtl *this);
