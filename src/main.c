#define LOG_LVL DBG
#include "log.h"
#include "gl.h"
#include "scene.h"
#include "result.h"

#include <stdio.h>
#include <stdlib.h>

#define WINDOW_W 600
#define WINDOW_H 600
#define WINDOW_TITLE "Wanderfern"

int main() {
    logi("Starting app");
    rci(!glfwInit(), EXIT_FAILURE, "Failed to initialize GLFW");
    GLFWwindow* window = glfwCreateWindow(WINDOW_W, WINDOW_H, WINDOW_TITLE, NULL, NULL);
    rci(!window, EXIT_FAILURE, "Failed to create GLFW window");
    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glViewport(0, 0, WINDOW_W, WINDOW_H);
    Scene *scene = try(scene_build(SID_MAINMENU), EXIT_FAILURE, "Failed to create scene");
    SceneUpdateCtx uctx = (SceneUpdateCtx) { .delta_time = 1.0f/60, .window = window };
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene->update(scene, &uctx);
        scene->draw(scene);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    scene_destroy(scene);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwDestroyWindow(window);
    glfwTerminate();
    logi("Terminating app");
    return EXIT_SUCCESS;
}
