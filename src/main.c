#define LOG_LVL DBG
#include "log.h"
#include "gl.h"
#include "scene.h"
#include "result.h"
#include "sprite.h"
#include "texture.h"
#include "mem.h"

#include <stdio.h>
#include <stdlib.h>

#define WINDOW_TITLE "Wanderfern"

int main() {
    logi("Starting app");
    Window window = try(gl_init(WINDOW_TITLE),
                        EXIT_FAILURE, "Failed to init OpenGL");
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window.gl_window);
    SceneUpdateCtx uctx = (SceneUpdateCtx) {
        .window = &window,
        .delta_time = 1/60.0f
    };
    SceneDrawCtx dctx = (SceneDrawCtx) {
        .window = &window,
        .delta_time = 1/60.0f
    };
    Scene *scene = try(scene_build(SID_MAINMENU, &window), EXIT_FAILURE, "Failed to create scene");
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
    reci(mem_used(), "Detect memory leak! unfree: %zu blocks", mem_used());
    logi("Terminating app");
    return EXIT_SUCCESS;
}
