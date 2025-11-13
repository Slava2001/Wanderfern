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
    Texture texture = try(texture_load("assets/cat.jpeg"), EXIT_FAILURE, "Failed to load texture");
    Sprite sprite = try(sprite_new(&texture, rect_new(0, 0, 1, 1)),
                        EXIT_FAILURE, "Failed to create sprite");
    SceneDrawCtx dctx = (SceneDrawCtx) {
        .window = &window,
        .delta_time = 1/60.0f
    };
    Transform transform = transform_new();

    while (!glfwWindowShouldClose(window.gl_window) &&
           glfwGetKey(window.gl_window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sprite.transform = transform_rotate(&sprite.transform, -0.01f, vec3d(1,1,1));
        sprite_draw(&sprite, &dctx, &transform);

        glfwSwapBuffers(window.gl_window);
        glfwPollEvents();
    }
    sprite_drop(&sprite);
    texture_drop(&texture);
    gl_deinit(&window);
    logi("Terminating app");
    return EXIT_SUCCESS;
}
