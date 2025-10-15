#pragma once

typedef struct Scene Scene;
struct Scene {
    int (*update)(void *ctx, float delta_time);
    int (*draw)(void *ctx);
};
