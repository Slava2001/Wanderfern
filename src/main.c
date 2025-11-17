#define LOG_LVL DBG
#include "log.h"
#include "gl.h"
#include "scene.h"
#include "result.h"
#include "sprite.h"
#include "texture.h"

#include <stdio.h>
#include <stdlib.h>

#define WINDOW_W 600
#define WINDOW_H 600
#define WINDOW_TITLE "Wanderfern"

int main() {
    logi("Starting app");
    Window window = try(gl_init(WINDOW_W, WINDOW_H, WINDOW_TITLE),
                        EXIT_FAILURE, "Failed to init OpenGL");

    SceneUpdateCtx uctx = (SceneUpdateCtx) {
        .window = &window,
        .delta_time = 1/60.0f
    };
    SceneDrawCtx dctx = (SceneDrawCtx) {
        .window = &window,
        .delta_time = 1/60.0f
    };
    Scene *scene = try(scene_build(SID_MAINMENU), EXIT_FAILURE, "Failed to create scene");
    while (!glfwWindowShouldClose(window.gl_window) &&
           glfwGetKey(window.gl_window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene->update(scene, &uctx);
        dctx.elapsed_time = glfwGetTime();
        scene->draw(scene, &dctx);
        glfwSwapBuffers(window.gl_window);
        glfwPollEvents();
    }
    scene->destroy(scene);
    gl_deinit(&window);
    logi("Terminating app");
    return EXIT_SUCCESS;
}
