#pragma once

#include "result.h"
#include "gl.h"

typedef struct SceneUpdateCtx {
    GLFWwindow *window;
    float delta_time;
} SceneUpdateCtx;

typedef struct Scene Scene;
struct Scene {
    int (*update)(void *ctx, const SceneUpdateCtx *update_ctx);
    int (*draw)(void *ctx);
    void (*destroy)(void *ctx);
};

enum SceneId {
    SID_MAINMENU
};

decl_result(ScenePtr, Scene*);

ResultScenePtr scene_build(enum SceneId id);
void scene_destroy(Scene *scene);
