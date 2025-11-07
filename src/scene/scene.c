#define LOG_LVL INFO
#include "scene.h"

#include "main_menu.h"

#include <stdlib.h>

ResultScenePtr scene_build(enum SceneId id) {
    logd("Enter");
    #define CASE(id, scene_type, builder)                                                    \
    case id:                                                                                 \
        logd("Creating scene, id: " #id);                                                    \
        scene_type *scene = (scene_type *)malloc(sizeof(scene_type));                        \
        rci(!scene, (ResultScenePtr) Err(), "Failed to allocate memory for new scene");      \
        *scene = try(builder(), (ResultScenePtr) Err(), "Failed to create scene. id: " #id); \
        logd("Scene created, id: " #id);                                                     \
        return (ResultScenePtr) Ok((Scene *)scene)
    switch (id) {
        CASE(SID_MAINMENU, MainMenu, main_menu_new);
        default:
    }
    #undef CASE
    loge("Failed to crater scene: unexpected id: %d", id);
    return (ResultScenePtr) Err();
}

void scene_destroy(Scene *scene) {
    if (scene->destroy) {
        scene->destroy(scene);
    }
    free(scene);
}
