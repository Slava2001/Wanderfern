#pragma once

#include "result.h"
#include "gl.h"
#include "transform.h"

typedef struct SceneUpdateCtx {
    Window *window;
    float delta_time;
} SceneUpdateCtx;

typedef struct SceneDrawCtx {
    Window *window;
    float delta_time;
} SceneDrawCtx;

typedef struct Scene Scene;
struct Scene {
    int (*update)(void *ctx, const SceneUpdateCtx *update_ctx);
    int (*draw)(void *ctx, const SceneDrawCtx *draw_ctx, const Transform *transform);
    void (*destroy)(void *ctx);
};

enum SceneId {
    SID_MAINMENU
};

decl_result(ScenePtr, Scene*);

ResultScenePtr scene_build(enum SceneId id);
void scene_destroy(Scene *scene);
